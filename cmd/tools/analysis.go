package main

// analysis.go contains advisory, read-only scans produced after extraction.
// The reports are intentionally not configuration: reviewed metadata remains
// authoritative and candidates require human confirmation.

import (
	"encoding/binary"
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"
)

type mipsInventory struct {
	SchemaVersion int                `json:"schema_version"`
	TargetID      string             `json:"target_id"`
	Source        string             `json:"source"`
	Modules       []mipsModuleReport `json:"modules"`
}

type mipsModuleReport struct {
	Module         string          `json:"module"`
	Path           string          `json:"path"`
	Bytes          int             `json:"bytes"`
	LoadAddress    string          `json:"load_address"`
	ScanStart      string          `json:"scan_start,omitempty"`
	ScanEnd        string          `json:"scan_end,omitempty"`
	ReviewedRanges int             `json:"reviewed_ranges"`
	ReviewedBytes  int             `json:"reviewed_bytes"`
	UncoveredBytes int             `json:"uncovered_bytes"`
	CallTargets    []mipsCandidate `json:"call_targets,omitempty"`
	BranchTargets  []mipsCandidate `json:"branch_targets,omitempty"`
	Status         string          `json:"status"`
}

type mipsCandidate struct {
	Address    string `json:"address"`
	References int    `json:"references"`
	Confidence string `json:"confidence"`
}

func (p project) buildAnalysis() error {
	config, err := p.loadConfig()
	if err != nil {
		return err
	}
	modules, err := loadModulesConfig(filepath.Join(p.root, "config", "modules.yaml"))
	if err != nil {
		return err
	}
	records, err := p.loadInventory()
	if err != nil {
		return err
	}
	report := mipsInventory{SchemaVersion: 1, TargetID: config.TargetID, Source: "build/extracted/inventory.json"}
	for _, module := range modules.Modules {
		record, ok := records[module.DiscPath]
		if !ok {
			return fmt.Errorf("module %s path %s is missing from inventory", module.ID, module.DiscPath)
		}
		item, err := analyzeModule(p, module, record)
		if err != nil {
			return err
		}
		report.Modules = append(report.Modules, item)
	}
	base := filepath.Join(p.root, "build", "analysis", "inventory")
	if err := os.MkdirAll(base, 0o755); err != nil {
		return err
	}
	data, err := json.MarshalIndent(report, "", "  ")
	if err != nil {
		return err
	}
	data = append(data, '\n')
	if err := os.WriteFile(filepath.Join(base, "mips-inventory.json"), data, 0o644); err != nil {
		return err
	}
	var summary strings.Builder
	fmt.Fprintf(&summary, "FFT MIPS analysis inventory\nmodules: %d\n\n", len(report.Modules))
	for _, item := range report.Modules {
		fmt.Fprintf(&summary, "%s %s: %s", item.Module, item.Path, item.Status)
		if item.ScanStart != "" {
			fmt.Fprintf(&summary, ", scan %s-%s, reviewed %d ranges/%d bytes, uncovered %d bytes, call candidates %d, branch candidates %d", item.ScanStart, item.ScanEnd, item.ReviewedRanges, item.ReviewedBytes, item.UncoveredBytes, len(item.CallTargets), len(item.BranchTargets))
		}
		summary.WriteByte('\n')
	}
	if err := os.WriteFile(filepath.Join(base, "README.txt"), []byte(summary.String()), 0o644); err != nil {
		return err
	}
	fmt.Printf("wrote MIPS analysis inventory to build/analysis/inventory\n")
	return nil
}

func (p project) loadInventory() (map[string]inventoryRecord, error) {
	data, err := os.ReadFile(p.inventoryPath)
	if err != nil {
		return nil, err
	}
	var value inventory
	if err := json.Unmarshal(data, &value); err != nil {
		return nil, fmt.Errorf("parse extracted inventory: %w", err)
	}
	result := make(map[string]inventoryRecord, len(value.Files))
	for _, record := range value.Files {
		result[record.Path] = record
	}
	return result, nil
}

func analyzeModule(p project, module moduleConfig, record inventoryRecord) (mipsModuleReport, error) {
	item := mipsModuleReport{Module: module.ID, Path: module.DiscPath, Bytes: module.Bytes, LoadAddress: module.LoadAddress}
	if module.LoadAddress == "unknown" {
		item.Status = "skipped: load address unknown"
		return item, nil
	}
	load, err := parseHex(module.LoadAddress, module.ID+" load address")
	if err != nil {
		return item, err
	}
	data, err := os.ReadFile(filepath.Join(p.filesRoot, filepath.FromSlash(module.DiscPath)))
	if err != nil {
		return item, err
	}
	fileBias := uint64(0)
	start := 0
	end := len(data)
	if module.Classification == "ps-x-exe" {
		textAddress, err := parseHex(record.TextAddress, module.ID+" text address")
		if err != nil {
			return item, err
		}
		start = psxEXEHeaderSize
		end = start + record.TextSize
		if end > len(data) {
			return item, fmt.Errorf("%s text range exceeds file", module.ID)
		}
		load = textAddress
		fileBias = psxEXEHeaderSize
	}
	item.ScanStart = fmt.Sprintf("0x%08x", load)
	item.ScanEnd = fmt.Sprintf("0x%08x", load+uint64(end-start))
	covered := make([]bool, end-start)
	for _, reconstruction := range module.Reconstructions {
		rangeStart, rangeEnd, err := parseInclusiveRange(reconstruction.FileRange)
		if err != nil {
			return item, err
		}
		rangeStart -= int(fileBias)
		rangeEnd -= int(fileBias)
		if rangeStart < start || rangeEnd > end {
			continue
		}
		for i := range covered[rangeStart-start : rangeEnd-start] {
			covered[rangeStart-start+i] = true
		}
		item.ReviewedRanges++
		item.ReviewedBytes += rangeEnd - rangeStart
	}
	reviewed := make(map[uint64]bool)
	symbols, err := p.reviewedSymbolsForModule(module.ID)
	if err != nil {
		return item, err
	}
	for _, symbol := range symbols.Symbols {
		address, err := parseHex(symbol.Address, module.ID+" reviewed symbol address")
		if err == nil {
			reviewed[address] = true
		}
	}
	for _, value := range covered {
		if !value {
			item.UncoveredBytes++
		}
	}
	callRefs, branchRefs := make(map[uint64]int), make(map[uint64]int)
	for offset := start; offset+4 <= end; offset += 4 {
		word := binary.LittleEndian.Uint32(data[offset : offset+4])
		pc := load + uint64(offset-start)
		op := word >> 26
		if op == 2 || op == 3 {
			target := (pc+4)&0xf0000000 | uint64(word&0x03ffffff)<<2
			if target >= load && target < load+uint64(end-start) {
				callRefs[target]++
			}
			continue
		}
		if op == 1 || (op >= 4 && op <= 7) || (op >= 20 && op <= 23) {
			delta := int64(int16(word&0xffff)) << 2
			target := uint64(int64(pc+4) + delta)
			if target >= load && target < load+uint64(end-start) {
				branchRefs[target]++
			}
		}
	}
	item.CallTargets = candidates(callRefs, reviewed)
	item.BranchTargets = candidates(branchRefs, reviewed)
	item.Status = "scanned"
	return item, nil
}

func candidates(refs map[uint64]int, reviewed map[uint64]bool) []mipsCandidate {
	addresses := make([]uint64, 0, len(refs))
	for address := range refs {
		if reviewed[address] {
			continue
		}
		addresses = append(addresses, address)
	}
	sort.Slice(addresses, func(i, j int) bool { return addresses[i] < addresses[j] })
	result := make([]mipsCandidate, 0, len(addresses))
	for _, address := range addresses {
		confidence := "low"
		if refs[address] >= 3 {
			confidence = "high"
		} else if refs[address] == 2 {
			confidence = "medium"
		}
		result = append(result, mipsCandidate{Address: fmt.Sprintf("0x%08x", address), References: refs[address], Confidence: confidence})
	}
	return result
}
