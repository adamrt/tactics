// decomp.go implements WIP drafting, comparison, and permutation workflows.
package main

import (
	"context"
	"crypto/sha256"
	"encoding/binary"
	"encoding/json"
	"errors"
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"sort"
	"strconv"
	"strings"
	"time"
)

const canonicalProfileName = "gcc-2.6.3_O2_aspsx-2.34"

type candidateRange struct {
	Module       moduleConfig
	Symbol       string
	RuntimeStart uint64
	RuntimeEnd   uint64
	FileStart    uint64
	FileEnd      uint64
	TargetPath   string
	Target       []byte
	Workspace    string
}

type candidateMetadata struct {
	Module       string `json:"module"`
	Symbol       string `json:"symbol"`
	Target       string `json:"target"`
	RuntimeStart string `json:"runtime_start"`
	RuntimeEnd   string `json:"runtime_end_exclusive"`
	FileStart    string `json:"file_start"`
	FileEnd      string `json:"file_end_exclusive"`
	Bytes        uint64 `json:"bytes"`
	Compiler     string `json:"compiler_profile"`
}

type explicitCandidate struct {
	TargetArg  string
	SourceArg  string
	LinkerArg  string
	TargetPath string
	SourcePath string
	LinkerPath string
	Start      uint64
	Length     uint64
	Expected   []byte
	Name       string
	BuildDir   string
	Profile    string
}

func (p project) candidateCommand(args []string) error {
	if len(args) == 0 {
		return errors.New("usage: tools wip draft|match|diff|prepare|permute ...")
	}
	switch args[0] {
	case "draft":
		return p.draftCandidate(args[1:])
	case "match":
		return p.matchCandidate(args[1:])
	case "diff":
		return p.diffCandidate(args[1:])
	case "prepare":
		return p.preparePermuter(args[1:])
	case "permute":
		return p.runPermuter(args[1:])
	default:
		return fmt.Errorf("unknown wip action %q; choose draft, match, diff, prepare, or permute", args[0])
	}
}

func moduleFileBias(classification string) (uint64, error) {
	switch classification {
	case "ps-x-exe":
		return psxEXEHeaderSize, nil
	case "raw-overlay":
		return 0, nil
	default:
		return 0, fmt.Errorf("unsupported candidate module classification %q", classification)
	}
}

func validModuleID(value string) bool {
	if value == "" {
		return false
	}
	for _, character := range value {
		if character >= 'a' && character <= 'z' || character >= '0' && character <= '9' || character == '-' {
			continue
		}
		return false
	}
	return true
}

func (p project) resolveCandidateRange(moduleID, symbol, startText, endText string) (candidateRange, error) {
	if !validModuleID(moduleID) {
		return candidateRange{}, fmt.Errorf("invalid module id %q", moduleID)
	}
	if !validSymbol(symbol) {
		return candidateRange{}, fmt.Errorf("invalid candidate symbol %q", symbol)
	}
	start, err := parseHex(startText, "candidate runtime start")
	if err != nil {
		return candidateRange{}, err
	}
	end, err := parseHex(endText, "candidate runtime end")
	if err != nil {
		return candidateRange{}, err
	}
	if start%4 != 0 || end%4 != 0 || end <= start {
		return candidateRange{}, errors.New("candidate runtime range must be nonempty, exclusive-ended, and 4-byte aligned")
	}

	modules, err := loadModulesConfig(filepath.Join(p.root, "config", "modules.yaml"))
	if err != nil {
		return candidateRange{}, err
	}
	var module *moduleConfig
	for index := range modules.Modules {
		if modules.Modules[index].ID == moduleID {
			if module != nil {
				return candidateRange{}, fmt.Errorf("modules config contains duplicate module %q", moduleID)
			}
			module = &modules.Modules[index]
		}
	}
	if module == nil {
		return candidateRange{}, fmt.Errorf("modules config has no module %q", moduleID)
	}
	loadAddress, err := parseHex(module.LoadAddress, moduleID+" load address")
	if err != nil {
		return candidateRange{}, err
	}
	bias, err := moduleFileBias(module.Classification)
	if err != nil {
		return candidateRange{}, err
	}
	if start < loadAddress || end < loadAddress {
		return candidateRange{}, fmt.Errorf("candidate range starts before %s load address 0x%x", moduleID, loadAddress)
	}
	fileStart := start - loadAddress + bias
	fileEnd := end - loadAddress + bias
	targetPath := filepath.Join(p.filesRoot, filepath.FromSlash(module.DiscPath))
	target, err := os.ReadFile(targetPath)
	if err != nil {
		return candidateRange{}, err
	}
	if module.Bytes != len(target) {
		return candidateRange{}, fmt.Errorf("%s target has %d bytes, modules config declares %d", moduleID, len(target), module.Bytes)
	}
	actualHash := fmt.Sprintf("%x", sha256.Sum256(target))
	if !strings.EqualFold(actualHash, module.SHA256) {
		return candidateRange{}, fmt.Errorf("%s target SHA-256 mismatch: got %s, expected %s", moduleID, actualHash, module.SHA256)
	}
	if fileStart > uint64(len(target)) || fileEnd > uint64(len(target)) {
		return candidateRange{}, fmt.Errorf("candidate file range 0x%x-0x%x lies outside %s", fileStart, fileEnd, module.DiscPath)
	}
	workspace := filepath.Join(p.root, "build", "analysis", "decomp", moduleID, symbol)
	return candidateRange{
		Module: *module, Symbol: symbol, RuntimeStart: start, RuntimeEnd: end,
		FileStart: fileStart, FileEnd: fileEnd, TargetPath: targetPath, Target: target,
		Workspace: workspace,
	}, nil
}

func (p project) reviewedSymbolsForModule(moduleID string) (symbolsConfig, error) {
	paths, err := filepath.Glob(filepath.Join(p.root, "config", "*symbols.yaml"))
	if err != nil {
		return symbolsConfig{}, err
	}
	var found *symbolsConfig
	for _, path := range paths {
		if filepath.Base(path) == "linker-symbols.yaml" {
			continue
		}
		config, err := loadSymbolsConfig(path)
		if err != nil {
			return symbolsConfig{}, err
		}
		if config.ModuleID != moduleID {
			continue
		}
		if found != nil {
			return symbolsConfig{}, fmt.Errorf("more than one reviewed symbol file describes module %q", moduleID)
		}
		copy := config
		found = &copy
	}
	if found == nil {
		return symbolsConfig{ModuleID: moduleID}, nil
	}
	return *found, nil
}

func writeJSON(path string, value any) error {
	data, err := json.MarshalIndent(value, "", "  ")
	if err != nil {
		return err
	}
	data = append(data, '\n')
	return os.WriteFile(path, data, 0o644)
}

func normalizeM2CAssembly(assembly []byte, start, end uint64) []byte {
	lines := strings.Split(string(assembly), "\n")
	internal := make(map[string]string)
	for _, line := range lines {
		fields := strings.Fields(line)
		if len(fields) != 2 || fields[0] != "alabel" || !strings.HasPrefix(fields[1], "func_") {
			continue
		}
		address, err := strconv.ParseUint(strings.TrimPrefix(fields[1], "func_"), 16, 64)
		if err == nil && address >= start && address < end {
			internal[fields[1]] = ".L" + strings.TrimPrefix(fields[1], "func_")
		}
	}
	if len(internal) == 0 {
		return assembly
	}
	output := make([]string, 0, len(lines))
	for _, line := range lines {
		fields := strings.Fields(line)
		if len(fields) == 2 && fields[0] == "alabel" {
			if _, ok := internal[fields[1]]; ok {
				continue
			}
		}
		for name, label := range internal {
			line = strings.ReplaceAll(line, name, label)
		}
		output = append(output, line)
	}
	for index, line := range output {
		fields := strings.Fields(line)
		jumpRegister := ""
		for fieldIndex, field := range fields {
			if field == "jr" && fieldIndex+1 < len(fields) {
				jumpRegister = fields[fieldIndex+1]
				break
			}
		}
		if jumpRegister == "" {
			continue
		}
		for previous := index - 1; previous >= 0 && previous >= index-8; previous-- {
			loadFields := strings.Fields(output[previous])
			for fieldIndex, field := range loadFields {
				if field != "lw" || fieldIndex+2 >= len(loadFields) || strings.TrimSuffix(loadFields[fieldIndex+1], ",") != jumpRegister {
					continue
				}
				addressField := loadFields[fieldIndex+2]
				if !strings.HasPrefix(addressField, "(0x") {
					continue
				}
				address := strings.TrimPrefix(addressField, "(")
				name := "jtbl_" + strings.TrimPrefix(address, "0x")
				constant := "(" + address + " & 0xFFFF)"
				output[previous] = strings.Replace(output[previous], constant, "%lo("+name+")", 1)
				for high := previous - 1; high >= 0 && high >= previous-4; high-- {
					highFields := strings.Fields(output[high])
					if len(highFields) >= 2 && highFields[len(highFields)-2] == "$at," && strings.HasPrefix(highFields[len(highFields)-1], "0x") {
						output[high] = strings.TrimSuffix(output[high], highFields[len(highFields)-1]) + "%hi(" + name + ")"
						break
					}
				}
				break
			}
		}
	}
	return []byte(strings.Join(output, "\n"))
}

func appendM2CJumpTables(assembly []byte, candidate candidateRange) ([]byte, error) {
	addresses := make(map[uint64]bool)
	for _, field := range strings.FieldsFunc(string(assembly), func(r rune) bool {
		return !(r >= '0' && r <= '9') && !(r >= 'A' && r <= 'Z') && !(r >= 'a' && r <= 'z') && r != '_'
	}) {
		if !strings.HasPrefix(field, "jtbl_") {
			continue
		}
		address, err := strconv.ParseUint(strings.TrimPrefix(field, "jtbl_"), 16, 64)
		if err != nil {
			return nil, fmt.Errorf("invalid generated jump-table name %q", field)
		}
		addresses[address] = true
	}
	if len(addresses) == 0 {
		return assembly, nil
	}
	ordered := make([]uint64, 0, len(addresses))
	for address := range addresses {
		ordered = append(ordered, address)
	}
	sort.Slice(ordered, func(i, j int) bool { return ordered[i] < ordered[j] })
	loadAddress, err := parseHex(candidate.Module.LoadAddress, candidate.Module.ID+" load address")
	if err != nil {
		return nil, err
	}
	bias, err := moduleFileBias(candidate.Module.Classification)
	if err != nil {
		return nil, err
	}
	var tables strings.Builder
	tables.WriteString("\n.section .rodata\n.align 2\n")
	targets := make(map[uint32]bool)
	for _, address := range ordered {
		if address < loadAddress {
			return nil, fmt.Errorf("jump table 0x%x is before module load address", address)
		}
		offset := address - loadAddress + bias
		entries := make([]uint32, 0, 256)
		for len(entries) < cap(entries) && offset+4 <= uint64(len(candidate.Target)) {
			value := binary.LittleEndian.Uint32(candidate.Target[offset : offset+4])
			if uint64(value) < candidate.RuntimeStart || uint64(value) >= candidate.RuntimeEnd {
				break
			}
			entries = append(entries, value)
			offset += 4
		}
		if len(entries) == 0 {
			return nil, fmt.Errorf("jump table 0x%x has no entries targeting the candidate range", address)
		}
		fmt.Fprintf(&tables, "jtbl_%08X:\n", address)
		for _, entry := range entries {
			targets[entry] = true
			fmt.Fprintf(&tables, "    .word .L%08X\n", entry)
		}
	}
	text := string(assembly)
	orderedTargets := make([]uint32, 0, len(targets))
	for target := range targets {
		orderedTargets = append(orderedTargets, target)
	}
	sort.Slice(orderedTargets, func(i, j int) bool { return orderedTargets[i] < orderedTargets[j] })
	for _, target := range orderedTargets {
		label := fmt.Sprintf(".L%08X:", target)
		if strings.Contains(text, label) {
			continue
		}
		marker := fmt.Sprintf(" %08X ", target)
		index := strings.Index(text, marker)
		if index < 0 {
			return nil, fmt.Errorf("jump-table target 0x%08x has no instruction in candidate assembly", target)
		}
		lineStart := strings.LastIndex(text[:index], "\n") + 1
		text = text[:lineStart] + label + "\n" + text[lineStart:]
	}
	return append([]byte(text), []byte(tables.String())...), nil
}

func (p project) draftCandidate(args []string) error {
	if len(args) != 4 && len(args) != 5 {
		return errors.New("usage: tools wip draft <module> <symbol> <runtime-start> <runtime-end-exclusive> [context-c]")
	}
	candidate, err := p.resolveCandidateRange(args[0], args[1], args[2], args[3])
	if err != nil {
		return err
	}
	if err := os.MkdirAll(candidate.Workspace, 0o755); err != nil {
		return err
	}
	expected := candidate.Target[candidate.FileStart:candidate.FileEnd]
	if err := os.WriteFile(filepath.Join(candidate.Workspace, "target.bin"), expected, 0o644); err != nil {
		return err
	}
	metadata := candidateMetadata{
		Module: candidate.Module.ID, Symbol: candidate.Symbol,
		Target:       filepath.ToSlash(strings.TrimPrefix(candidate.TargetPath, p.root+string(filepath.Separator))),
		RuntimeStart: fmt.Sprintf("0x%08x", candidate.RuntimeStart), RuntimeEnd: fmt.Sprintf("0x%08x", candidate.RuntimeEnd),
		FileStart: fmt.Sprintf("0x%x", candidate.FileStart), FileEnd: fmt.Sprintf("0x%x", candidate.FileEnd),
		Bytes: candidate.FileEnd - candidate.FileStart, Compiler: canonicalProfileName,
	}
	if err := writeJSON(filepath.Join(candidate.Workspace, "metadata.json"), metadata); err != nil {
		return err
	}

	symbols, err := p.reviewedSymbolsForModule(candidate.Module.ID)
	if err != nil {
		return err
	}
	functionsPath := filepath.Join(candidate.Workspace, "functions.csv")
	var functions strings.Builder
	seenAddress := false
	for _, symbol := range symbols.Symbols {
		if symbol.Kind != "function" {
			continue
		}
		address, err := parseHex(symbol.Address, "reviewed symbol address")
		if err != nil {
			return err
		}
		name := symbol.Name
		if address == candidate.RuntimeStart {
			name = candidate.Symbol
			seenAddress = true
		}
		fmt.Fprintf(&functions, "%08X,%s\n", address, name)
	}
	if !seenAddress {
		fmt.Fprintf(&functions, "%08X,%s\n", candidate.RuntimeStart, candidate.Symbol)
	}
	if err := os.WriteFile(functionsPath, []byte(functions.String()), 0o644); err != nil {
		return err
	}

	assemblyDir := filepath.Join(candidate.Workspace, "assembly")
	if err := os.RemoveAll(assemblyDir); err != nil {
		return err
	}
	spimArgs := []string{
		"singleFileDisasm", candidate.TargetPath, assemblyDir,
		"--start", fmt.Sprintf("0x%x", candidate.FileStart), "--end", fmt.Sprintf("0x%x", candidate.FileEnd),
		"--vram", fmt.Sprintf("0x%x", candidate.RuntimeStart), "--functions", functionsPath,
		"--instr-category", "r3000gte", "--compiler", "GCC", "--endian", "little", "--abi", "O32", "--arch-level", "MIPS1",
		"--no-default-banned", "--no-libultra-syms", "--no-ique-syms", "--no-hardware-regs", "--no-pic",
		"--no-string-guesser", "--no-aggressive-string-guesser", "--no-allow-unksegment",
		"--asm-comments", "--no-pseudo-instr", "--no-j-branch", "--asm-ent-label", ".ent", "--asm-end-label", ".end",
		"--asm-func-as-label", "--asm-emit-size-directive",
	}
	if err := runInDir(p.root, spimArgs...); err != nil {
		return err
	}
	assemblyFiles, err := filepath.Glob(filepath.Join(assemblyDir, "*.text.s"))
	if err != nil {
		return err
	}
	if len(assemblyFiles) != 1 {
		return fmt.Errorf("spimdisasm produced %d text assembly files in %s", len(assemblyFiles), assemblyDir)
	}
	assembly, err := os.ReadFile(assemblyFiles[0])
	if err != nil {
		return err
	}
	m2cAssembly := normalizeM2CAssembly(assembly, candidate.RuntimeStart, candidate.RuntimeEnd)
	m2cAssembly, err = appendM2CJumpTables(m2cAssembly, candidate)
	if err != nil {
		return err
	}
	m2cAssemblyPath := filepath.Join(candidate.Workspace, "candidate.m2c.s")
	if err := os.WriteFile(m2cAssemblyPath, m2cAssembly, 0o644); err != nil {
		return err
	}

	m2cArgs := []string{
		"m2c", "-t", "mipsel-gcc-c", "--valid-syntax", "--deterministic-vars", "--hex-case",
		"--comment-style=oneline", "--no-cache", "--globals=used", "-f", candidate.Symbol,
	}
	if len(args) == 5 {
		contextPath, err := projectPath(p.root, args[4], "m2c context")
		if err != nil {
			return err
		}
		preprocessed := filepath.Join(candidate.Workspace, "context.i")
		if err := runInDir(p.root, "mipsel-linux-gnu-cpp", "-P", "-undef", "-nostdinc", "-Iinclude", contextPath, "-o", preprocessed); err != nil {
			return err
		}
		m2cArgs = append(m2cArgs, "--context", preprocessed)
	}
	m2cArgs = append(m2cArgs, m2cAssemblyPath)
	command := exec.Command(m2cArgs[0], m2cArgs[1:]...)
	command.Dir = p.root
	command.Stderr = os.Stderr
	draft, err := command.Output()
	if err != nil {
		return fmt.Errorf("m2c: %w", err)
	}
	draftPath := filepath.Join(candidate.Workspace, "draft.c")
	if err := os.WriteFile(draftPath, draft, 0o644); err != nil {
		return err
	}
	fmt.Printf("wip draft: %s (%d bytes, runtime 0x%08x-0x%08x exclusive)\n", draftPath, len(expected), candidate.RuntimeStart, candidate.RuntimeEnd)
	return nil
}

func (p project) resolveExplicitCandidate(args []string) (explicitCandidate, error) {
	if len(args) != 5 && len(args) != 6 {
		return explicitCandidate{}, errors.New("usage: <target> <source> <linker-script> <file-offset> <bytes> [profile]")
	}
	profileName := canonicalProfileName
	if len(args) == 6 {
		profileName = args[5]
	}
	if _, ok := compilerProfileNamed(profileName); !ok {
		return explicitCandidate{}, fmt.Errorf("unsupported compiler profile %q", profileName)
	}
	targetPath, err := projectPath(p.root, args[0], "candidate target")
	if err != nil {
		return explicitCandidate{}, err
	}
	sourcePath, err := projectPath(p.root, args[1], "wip source")
	if err != nil {
		return explicitCandidate{}, err
	}
	linkerPath, err := projectPath(p.root, args[2], "candidate linker script")
	if err != nil {
		return explicitCandidate{}, err
	}
	start, err := parseHex(args[3], "candidate file offset")
	if err != nil {
		return explicitCandidate{}, err
	}
	length, err := parseHex(args[4], "candidate byte count")
	if err != nil {
		return explicitCandidate{}, err
	}
	if length == 0 {
		return explicitCandidate{}, errors.New("candidate byte count must be nonzero")
	}
	target, err := os.ReadFile(targetPath)
	if err != nil {
		return explicitCandidate{}, err
	}
	if start > uint64(len(target)) || length > uint64(len(target))-start {
		return explicitCandidate{}, fmt.Errorf("candidate range 0x%x-0x%x is outside %s", start, start+length, args[0])
	}
	name := strings.TrimSuffix(filepath.Base(sourcePath), filepath.Ext(sourcePath))
	return explicitCandidate{
		TargetArg: args[0], SourceArg: args[1], LinkerArg: args[2], TargetPath: targetPath,
		SourcePath: sourcePath, LinkerPath: linkerPath, Start: start, Length: length,
		Expected: target[start : start+length], Name: name,
		BuildDir: filepath.Join(p.root, "build", "wip", name),
		Profile:  profileName,
	}, nil
}

func (p project) compileExplicitCandidate(candidate explicitCandidate) ([]byte, compilerProfile, error) {
	profile, ok := compilerProfileNamed(candidate.Profile)
	if !ok {
		return nil, compilerProfile{}, fmt.Errorf("compiler profile %q is unavailable", candidate.Profile)
	}
	compiled, err := p.compileHistoricalC(candidate.SourcePath, candidate.LinkerPath, candidate.BuildDir, profile)
	return compiled, profile, err
}

func asmDifferSettings(candidateBinary string) string {
	return fmt.Sprintf(`def apply(config, args):
    config["arch"] = "mipsel"
    config["baseimg"] = "target.bin"
    config["myimg"] = %q
    config["objdump_executable"] = "mipsel-linux-gnu-objdump"
    config["show_line_numbers_default"] = False
`, candidateBinary)
}

func (p project) diffCandidate(args []string) error {
	candidate, err := p.resolveExplicitCandidate(args)
	if err != nil {
		return fmt.Errorf("usage: tools wip diff <target> <source> <linker-script> <file-offset> <bytes> [profile]: %w", err)
	}
	compiled, profile, err := p.compileExplicitCandidate(candidate)
	if err != nil {
		return err
	}
	if err := os.WriteFile(filepath.Join(candidate.BuildDir, "target.bin"), candidate.Expected, 0o644); err != nil {
		return err
	}
	candidateBinary := profile.name + ".bin"
	settingsPath := filepath.Join(candidate.BuildDir, "diff_settings.py")
	if err := os.WriteFile(settingsPath, []byte(asmDifferSettings(candidateBinary)), 0o644); err != nil {
		return err
	}
	command := exec.Command(
		"asm-differ", "--format", "plain", "--no-pager", "--width", "64", "-U", "3",
		"0", fmt.Sprintf("0x%x", max(len(candidate.Expected), len(compiled))),
	)
	command.Dir = candidate.BuildDir
	output, err := command.CombinedOutput()
	if err != nil {
		return fmt.Errorf("asm-differ: %w: %s", err, strings.TrimSpace(string(output)))
	}
	diffPath := filepath.Join(candidate.BuildDir, "diff.txt")
	if err := os.WriteFile(diffPath, output, 0o644); err != nil {
		return err
	}
	os.Stdout.Write(output)
	if offset, differs := mismatch(candidate.Expected, compiled); differs {
		fmt.Printf("wip diff: %s\n", diffPath)
		fmt.Print(mismatchDiagnostics(candidate.Expected, compiled, offset, candidate.Start))
		return fmt.Errorf("wip %s does not match (%d target bytes, %d compiled bytes)", candidate.SourceArg, len(candidate.Expected), len(compiled))
	}
	fmt.Printf("matching WIP: %s (%d bytes, profile %s)\n", candidate.SourceArg, len(compiled), profile.name)
	return nil
}

func linkerTextAddress(linkerPath string) (uint64, error) {
	data, err := os.ReadFile(linkerPath)
	if err != nil {
		return 0, err
	}
	text := string(data)
	marker := ".text"
	index := strings.Index(text, marker)
	if index < 0 {
		return 0, errors.New("linker script has no .text output section")
	}
	fields := strings.Fields(text[index+len(marker):])
	if len(fields) == 0 {
		return 0, errors.New("linker script has no .text address")
	}
	return parseHex(fields[0], "linker .text address")
}

func permuterSettings(functionName string) string {
	return fmt.Sprintf("func_name = %q\ncompiler_type = \"gcc\"\nobjdump_command = \"mipsel-linux-gnu-objdump -drz -m mips:3000\"\n", functionName)
}

func (p project) preparePermuter(args []string) error {
	candidate, err := p.resolveExplicitCandidate(args)
	if err != nil {
		return fmt.Errorf("usage: tools wip prepare <target> <source> <linker-script> <file-offset> <bytes> [profile]: %w", err)
	}
	address, err := linkerTextAddress(candidate.LinkerPath)
	if err != nil {
		return err
	}
	workspace := filepath.Join(p.root, "build", "analysis", "decomp", candidate.Name, "permuter")
	if err := os.RemoveAll(workspace); err != nil {
		return err
	}
	if err := os.MkdirAll(workspace, 0o755); err != nil {
		return err
	}
	if err := os.WriteFile(filepath.Join(workspace, "target.bin"), candidate.Expected, 0o644); err != nil {
		return err
	}
	basePath := filepath.Join(workspace, "base.c")
	if err := runInDir(p.root, "mipsel-linux-gnu-cpp", "-P", "-undef", "-nostdinc", "-Iinclude", candidate.SourcePath, "-o", basePath); err != nil {
		return err
	}
	targetAssembly := fmt.Sprintf(`.set noreorder
.section .text
.globl %s
.type %s, @function
%s:
.incbin "target.bin"
.size %s, . - %s
`, candidate.Name, candidate.Name, candidate.Name, candidate.Name, candidate.Name)
	if err := os.WriteFile(filepath.Join(workspace, "target.s"), []byte(targetAssembly), 0o644); err != nil {
		return err
	}
	if err := runInDir(workspace, "mipsel-linux-gnu-as", "-EL", "-march=r3000", "-mtune=r3000", "-no-pad-sections", "-O1", "-G0", "-o", "target-raw.o", "target.s"); err != nil {
		return err
	}
	targetLinker := fmt.Sprintf("OUTPUT_ARCH(mips)\nSECTIONS { .text 0x%08x : SUBALIGN(4) { *(.text) } /DISCARD/ : { *(.reginfo) *(.pdr) *(.comment) *(.gnu.attributes) } }\n", address)
	if err := os.WriteFile(filepath.Join(workspace, "target.ld"), []byte(targetLinker), 0o644); err != nil {
		return err
	}
	if err := runInDir(workspace, "mipsel-linux-gnu-ld", "-EL", "-T", "target.ld", "-o", "target.o", "target-raw.o"); err != nil {
		return err
	}
	relativeLinker, err := filepath.Rel(p.root, candidate.LinkerPath)
	if err != nil {
		return err
	}
	compileScript := fmt.Sprintf("#!/bin/sh\nset -eu\n/usr/local/bin/tools compile-permuter-input %q \"$1\" \"$3\" %q\n", filepath.ToSlash(relativeLinker), candidate.Profile)
	compilePath := filepath.Join(workspace, "compile.sh")
	if err := os.WriteFile(compilePath, []byte(compileScript), 0o755); err != nil {
		return err
	}
	settings := permuterSettings(candidate.Name)
	if err := os.WriteFile(filepath.Join(workspace, "settings.toml"), []byte(settings), 0o644); err != nil {
		return err
	}
	command := exec.Command("decomp-permuter", "--debug", ".")
	command.Dir, command.Stdout, command.Stderr = workspace, os.Stdout, os.Stderr
	if err := command.Run(); err != nil {
		return fmt.Errorf("decomp-permuter debug validation: %w", err)
	}
	fmt.Printf("permuter workspace: %s\n", workspace)
	return nil
}

func temporaryPermuterPath(path string, mustExist bool) error {
	clean := filepath.Clean(path)
	temporaryRoot := filepath.Clean(os.TempDir()) + string(filepath.Separator)
	if !filepath.IsAbs(clean) || !strings.HasPrefix(clean, temporaryRoot) {
		return fmt.Errorf("permuter temporary path must be inside %s", os.TempDir())
	}
	if mustExist {
		info, err := os.Stat(clean)
		if err != nil {
			return err
		}
		if !info.Mode().IsRegular() {
			return fmt.Errorf("permuter input is not a regular file: %s", clean)
		}
	}
	return nil
}

func copyFile(source, destination string, mode os.FileMode) error {
	data, err := os.ReadFile(source)
	if err != nil {
		return err
	}
	return os.WriteFile(destination, data, mode)
}

func (p project) compilePermuterInput(args []string) error {
	if len(args) != 3 && len(args) != 4 {
		return errors.New("usage: tools compile-permuter-input <linker-script> <temporary-source> <temporary-output> [profile]")
	}
	linkerPath, err := projectPath(p.root, args[0], "permuter linker script")
	if err != nil {
		return err
	}
	if err := temporaryPermuterPath(args[1], true); err != nil {
		return err
	}
	if err := temporaryPermuterPath(args[2], false); err != nil {
		return err
	}
	parent := filepath.Join(p.root, "build", "analysis", "permuter-compile")
	if err := os.MkdirAll(parent, 0o755); err != nil {
		return err
	}
	buildDir, err := os.MkdirTemp(parent, "run-")
	if err != nil {
		return err
	}
	defer os.RemoveAll(buildDir)
	profileName := canonicalProfileName
	if len(args) == 4 {
		profileName = args[3]
	}
	profile, ok := compilerProfileNamed(profileName)
	if !ok {
		return fmt.Errorf("unsupported compiler profile %q", profileName)
	}
	// The permuter callback must produce an ELF file for its temporary output;
	// a cached section-only result deliberately skips ELF creation.
	previousCache, hadCache := os.LookupEnv("TOOLS_CACHE")
	if err := os.Setenv("TOOLS_CACHE", "0"); err != nil {
		return err
	}
	defer func() {
		if hadCache {
			_ = os.Setenv("TOOLS_CACHE", previousCache)
		} else {
			_ = os.Unsetenv("TOOLS_CACHE")
		}
	}()
	if _, err := p.compileHistoricalC(args[1], linkerPath, buildDir, profile); err != nil {
		return err
	}
	return copyFile(filepath.Join(buildDir, profile.name+".elf"), args[2], 0o600)
}

func projectDirectory(root, value, field string) (string, error) {
	clean := filepath.Clean(filepath.FromSlash(value))
	if filepath.IsAbs(clean) || clean == ".." || strings.HasPrefix(clean, ".."+string(filepath.Separator)) {
		return "", fmt.Errorf("%s must stay inside the project: %q", field, value)
	}
	path := filepath.Join(root, clean)
	info, err := os.Stat(path)
	if err != nil {
		return "", err
	}
	if !info.IsDir() {
		return "", fmt.Errorf("%s is not a directory: %q", field, value)
	}
	return path, nil
}

func (p project) runPermuter(args []string) error {
	if len(args) != 3 {
		return errors.New("usage: tools wip permute <workspace> <seconds> <jobs>")
	}
	workspace, err := projectDirectory(p.root, args[0], "permuter workspace")
	if err != nil {
		return err
	}
	seconds, err := strconv.Atoi(args[1])
	if err != nil || seconds < 1 || seconds > 3600 {
		return errors.New("permuter duration must be between 1 and 3600 seconds")
	}
	jobs, err := strconv.Atoi(args[2])
	if err != nil || jobs < 1 || jobs > 64 {
		return errors.New("permuter jobs must be between 1 and 64")
	}
	ctx, cancel := context.WithTimeout(context.Background(), time.Duration(seconds)*time.Second)
	defer cancel()
	command := exec.CommandContext(ctx, "decomp-permuter", "--better-only", "--best-only", "--stop-on-zero", "-j", strconv.Itoa(jobs), ".")
	command.Dir, command.Stdout, command.Stderr = workspace, os.Stdout, os.Stderr
	err = command.Run()
	if ctx.Err() == context.DeadlineExceeded {
		fmt.Printf("permuter stopped after %d seconds; reviewed outputs remain in %s\n", seconds, workspace)
		return nil
	}
	if err != nil {
		return fmt.Errorf("decomp-permuter: %w", err)
	}
	return nil
}
