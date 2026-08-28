// maintenance.go provides extraction, configuration checks, and source inventories.
package main

import (
	"encoding/hex"
	"errors"
	"fmt"
	"io/fs"
	"path/filepath"
	"sort"
)

func (p project) toolsCommand(args []string) error {
	if len(args) != 1 {
		return errors.New("usage: tools check-config|extract|analyze")
	}
	switch args[0] {
	case "check-config":
		return p.checkConfig()
	case "extract":
		return p.extractDisc()
	case "analyze":
		return p.buildAnalysis()
	default:
		return fmt.Errorf("unknown tools action %q; choose check-config, extract, or analyze", args[0])
	}
}

func validSHA256(value string) bool {
	decoded, err := hex.DecodeString(value)
	return err == nil && len(decoded) == 32
}

func validateModulesStructure(config modulesConfig, root string) error {
	if config.TargetID == "" || len(config.Modules) == 0 {
		return errors.New("modules config is missing target identity or modules")
	}
	seenModules := make(map[string]bool)
	seenDiscPaths := make(map[string]bool)
	seenSources := make(map[string]bool)
	for _, module := range config.Modules {
		if !validModuleID(module.ID) || seenModules[module.ID] {
			return fmt.Errorf("invalid or duplicate module id %q", module.ID)
		}
		seenModules[module.ID] = true
		if module.DiscPath == "" || seenDiscPaths[module.DiscPath] {
			return fmt.Errorf("module %s has missing or duplicate disc_path %q", module.ID, module.DiscPath)
		}
		seenDiscPaths[module.DiscPath] = true
		if module.Bytes <= 0 || module.LBA <= 0 || !validSHA256(module.SHA256) {
			return fmt.Errorf("module %s has invalid bytes, lba, or sha256", module.ID)
		}
		var loadAddress uint64
		if len(module.Reconstructions) > 0 {
			var err error
			loadAddress, err = parseHex(module.LoadAddress, module.ID+" load_address")
			if err != nil {
				return err
			}
		} else if module.LoadAddress != "unknown" {
			if _, err := parseHex(module.LoadAddress, module.ID+" load_address"); err != nil {
				return err
			}
		}
		bias, err := moduleFileBias(module.Classification)
		if err != nil {
			return fmt.Errorf("module %s: %w", module.ID, err)
		}
		reconstructions := append([]reconstructionConfig(nil), module.Reconstructions...)
		sort.SliceStable(reconstructions, func(i, j int) bool {
			left, _, leftErr := parseInclusiveRange(reconstructions[i].FileRange)
			right, _, rightErr := parseInclusiveRange(reconstructions[j].FileRange)
			return leftErr == nil && (rightErr != nil || left < right)
		})
		previousEnd := -1
		seenSymbols := make(map[string]bool)
		for index, reconstruction := range reconstructions {
			label := fmt.Sprintf("module %s reconstruction %d (%s)", module.ID, index+1, reconstruction.Symbol)
			if !validSymbol(reconstruction.Symbol) || seenSymbols[reconstruction.Symbol] {
				return fmt.Errorf("%s has invalid or duplicate symbol", label)
			}
			seenSymbols[reconstruction.Symbol] = true
			start, end, err := parseInclusiveRange(reconstruction.FileRange)
			if err != nil {
				return fmt.Errorf("%s: %w", label, err)
			}
			if previousEnd >= 0 && start < previousEnd {
				return fmt.Errorf("%s overlaps the previous reconstruction", label)
			}
			if end > module.Bytes || reconstruction.Bytes != end-start {
				return fmt.Errorf("%s has an invalid byte range", label)
			}
			address, err := parseHex(reconstruction.Address, label+" address")
			if err != nil {
				return err
			}
			if address < loadAddress || address-loadAddress+bias != uint64(start) {
				return fmt.Errorf("%s address does not map to its file range", label)
			}
			if reconstruction.Language != "c" || reconstruction.Status != "matching" {
				return fmt.Errorf("%s must be matching C", label)
			}
			profileName := reconstruction.CanonicalProfile
			if profileName == "" {
				profileName = canonicalProfileName
			}
			if _, ok := compilerProfileNamed(profileName); !ok {
				return fmt.Errorf("%s uses unsupported compiler profile %q", label, profileName)
			}
			if _, err := projectPath(root, reconstruction.Source, "source"); err != nil {
				return fmt.Errorf("%s: %w", label, err)
			}
			seenSections := make(map[string]bool)
			for _, extra := range reconstruction.VerifiedRanges {
				if extra.Section == "" || extra.Section == ".text" || seenSections[extra.Section] {
					return fmt.Errorf("%s has invalid or duplicate verified section %q", label, extra.Section)
				}
				seenSections[extra.Section] = true
				extraStart, extraEnd, err := parseInclusiveRange(extra.FileRange)
				if err != nil || extraEnd > module.Bytes || extra.Bytes != extraEnd-extraStart {
					return fmt.Errorf("%s section %s has an invalid byte range", label, extra.Section)
				}
				extraAddress, err := parseHex(extra.Address, label+" section address")
				if err != nil {
					return err
				}
				if extraAddress < loadAddress || extraAddress-loadAddress+bias != uint64(extraStart) {
					return fmt.Errorf("%s section %s address does not map to its file range", label, extra.Section)
				}
			}
			seenSources[reconstruction.Source] = true
			previousEnd = end
		}
	}
	return validateSourceInventory(root, "src", seenSources, "matching reconstruction")
}

func validateCandidates(config candidatesConfig, modules modulesConfig, root string) error {
	if config.TargetID != modules.TargetID {
		return errors.New("wip target_id does not match modules target_id")
	}
	moduleByID := make(map[string]moduleConfig)
	matchingSymbols := make(map[string]bool)
	for _, module := range modules.Modules {
		moduleByID[module.ID] = module
		for _, reconstruction := range module.Reconstructions {
			matchingSymbols[module.ID+"\x00"+reconstruction.Symbol] = true
		}
	}
	seen := make(map[string]bool)
	sources := make(map[string]bool)
	for index, candidate := range config.Candidates {
		label := fmt.Sprintf("wip %d (%s)", index+1, candidate.Symbol)
		module, ok := moduleByID[candidate.Module]
		if !ok || !validSymbol(candidate.Symbol) || candidate.Status != "wip" {
			return fmt.Errorf("%s has invalid module, symbol, or status", label)
		}
		key := candidate.Module + "\x00" + candidate.Symbol
		if seen[key] || matchingSymbols[key] {
			return fmt.Errorf("%s duplicates another WIP entry or matching reconstruction", label)
		}
		seen[key] = true
		address, err := parseHex(candidate.Address, label+" address")
		if err != nil {
			return err
		}
		loadAddress, _ := parseHex(module.LoadAddress, "load address")
		if address < loadAddress || address%4 != 0 {
			return fmt.Errorf("%s has invalid runtime address", label)
		}
		if _, ok := compilerProfileNamed(candidate.CanonicalProfile); !ok {
			return fmt.Errorf("%s uses unsupported compiler profile %q", label, candidate.CanonicalProfile)
		}
		if _, err := projectPath(root, candidate.Source, "wip source"); err != nil {
			return fmt.Errorf("%s: %w", label, err)
		}
		if sources[candidate.Source] {
			return fmt.Errorf("wip source %s is referenced more than once", candidate.Source)
		}
		sources[candidate.Source] = true
	}
	return validateSourceInventory(root, "wip", sources, "wip manifest")
}

func validateSourceInventory(root, relative string, expected map[string]bool, owner string) error {
	base := filepath.Join(root, filepath.FromSlash(relative))
	seen := make(map[string]bool)
	err := filepath.WalkDir(base, func(path string, entry fs.DirEntry, err error) error {
		if err != nil {
			return err
		}
		if entry.IsDir() || filepath.Ext(path) != ".c" {
			return nil
		}
		rel, err := filepath.Rel(root, path)
		if err != nil {
			return err
		}
		name := filepath.ToSlash(rel)
		seen[name] = true
		if !expected[name] {
			return fmt.Errorf("orphan C source %s is not in the %s", name, owner)
		}
		return nil
	})
	if err != nil {
		return err
	}
	for name := range expected {
		if !seen[name] {
			return fmt.Errorf("%s references source outside %s: %s", owner, relative, name)
		}
	}
	return nil
}

func (p project) checkConfig() error {
	base := filepath.Join(p.root, "config")
	modules, err := loadModulesConfig(filepath.Join(base, "modules.yaml"))
	if err != nil {
		return err
	}
	if err := validateModulesStructure(modules, p.root); err != nil {
		return err
	}
	candidates, err := loadCandidatesConfig(filepath.Join(base, "wip.yaml"))
	if err != nil {
		return err
	}
	if err := validateCandidates(candidates, modules, p.root); err != nil {
		return err
	}
	linkers, err := loadLinkerSymbolsConfig(filepath.Join(base, "linker-symbols.yaml"))
	if err != nil {
		return err
	}
	if err := validateLinkerSymbols(linkers, modules); err != nil {
		return err
	}
	paths, err := filepath.Glob(filepath.Join(base, "*symbols.yaml"))
	if err != nil {
		return err
	}
	seenSymbolModules := make(map[string]bool)
	for _, path := range paths {
		if filepath.Base(path) == "linker-symbols.yaml" {
			continue
		}
		symbols, err := loadSymbolsConfig(path)
		if err != nil {
			return err
		}
		if seenSymbolModules[symbols.ModuleID] {
			return fmt.Errorf("more than one symbol inventory describes module %s", symbols.ModuleID)
		}
		seenSymbolModules[symbols.ModuleID] = true
		if err := validateReconstructionSymbols(modules, symbols); err != nil {
			return err
		}
		linkModule, err := linkers.module(symbols.ModuleID)
		if err != nil {
			return err
		}
		if err := validateReviewedSymbolLinkerAddresses(symbols, linkModule); err != nil {
			return err
		}
	}
	for _, module := range modules.Modules {
		if len(module.Reconstructions) > 0 && !seenSymbolModules[module.ID] {
			return fmt.Errorf("module %s has reconstructions but no symbol inventory", module.ID)
		}
	}
	libraries, err := loadLibrariesConfig(filepath.Join(base, "libraries.yaml"))
	if err != nil {
		return err
	}
	mainSymbols, err := loadSymbolsConfig(filepath.Join(base, "main-symbols.yaml"))
	if err != nil {
		return err
	}
	if err := validateLibraryRanges(libraries, mainSymbols); err != nil {
		return err
	}
	fmt.Printf("config exact: %d modules, %d matching reconstructions (%d bytes), %d tracked WIP entries\n", len(modules.Modules), reconstructionCount(modules), reconstructionBytes(modules), len(candidates.Candidates))
	return nil
}

func reconstructionCount(modules modulesConfig) int {
	total := 0
	for _, module := range modules.Modules {
		total += len(module.Reconstructions)
	}
	return total
}

func reconstructionBytes(modules modulesConfig) int {
	total := 0
	for _, module := range modules.Modules {
		for _, reconstruction := range module.Reconstructions {
			total += reconstruction.Bytes
		}
	}
	return total
}
