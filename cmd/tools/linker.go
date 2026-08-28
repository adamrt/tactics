// linker.go generates the temporary linker scripts used by reconstruction builds.
package main

import (
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"

	"gopkg.in/yaml.v3"
)

type linkerSymbolsConfig struct {
	SchemaVersion int                   `yaml:"schema_version"`
	TargetID      string                `yaml:"target_id"`
	Modules       []linkerModuleSymbols `yaml:"modules"`
}

type linkerModuleSymbols struct {
	ID        string                       `yaml:"id"`
	Symbols   map[string]string            `yaml:"symbols"`
	Overrides map[string]map[string]string `yaml:"overrides"`
}

func loadLinkerSymbolsConfig(path string) (linkerSymbolsConfig, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return linkerSymbolsConfig{}, err
	}
	var config linkerSymbolsConfig
	if err := yaml.Unmarshal(data, &config); err != nil {
		return linkerSymbolsConfig{}, fmt.Errorf("parse linker symbols config: %w", err)
	}
	if config.SchemaVersion != 1 || config.TargetID == "" {
		return linkerSymbolsConfig{}, errors.New("unsupported or incomplete linker symbols config")
	}
	return config, nil
}

func (config linkerSymbolsConfig) module(id string) (linkerModuleSymbols, error) {
	var found *linkerModuleSymbols
	for index := range config.Modules {
		if config.Modules[index].ID != id {
			continue
		}
		if found != nil {
			return linkerModuleSymbols{}, fmt.Errorf("linker symbols contains duplicate module %s", id)
		}
		copy := config.Modules[index]
		found = &copy
	}
	if found == nil {
		return linkerModuleSymbols{}, fmt.Errorf("linker symbols has no module %s", id)
	}
	return *found, nil
}

func validateLinkerSymbols(config linkerSymbolsConfig, modules modulesConfig) error {
	if config.TargetID != modules.TargetID {
		return errors.New("linker symbols target_id does not match modules target_id")
	}
	seenModules := make(map[string]bool)
	moduleIDs := make(map[string]bool)
	for _, module := range modules.Modules {
		moduleIDs[module.ID] = true
	}
	for _, module := range config.Modules {
		if !moduleIDs[module.ID] || seenModules[module.ID] {
			return fmt.Errorf("linker symbols has unknown or duplicate module %q", module.ID)
		}
		seenModules[module.ID] = true
		for name, address := range module.Symbols {
			if !validSymbol(name) {
				return fmt.Errorf("module %s has invalid linker symbol %q", module.ID, name)
			}
			if _, err := parseHex(address, "linker symbol address"); err != nil {
				return fmt.Errorf("module %s linker symbol %s: %w", module.ID, name, err)
			}
		}
		for reconstruction, overrides := range module.Overrides {
			if !validSymbol(reconstruction) {
				return fmt.Errorf("module %s has invalid linker override owner %q", module.ID, reconstruction)
			}
			for name, address := range overrides {
				if _, ok := module.Symbols[name]; !ok {
					return fmt.Errorf("module %s override %s references unknown linker symbol %s", module.ID, reconstruction, name)
				}
				if _, err := parseHex(address, "linker override address"); err != nil {
					return err
				}
			}
		}
	}
	for id := range moduleIDs {
		if !seenModules[id] {
			return fmt.Errorf("linker symbols has no module %s", id)
		}
	}
	return nil
}

func validateReviewedSymbolLinkerAddresses(symbols symbolsConfig, module linkerModuleSymbols) error {
	if symbols.ModuleID != module.ID {
		return errors.New("reviewed symbols and linker symbols do not describe the same module")
	}
	for _, symbol := range symbols.Symbols {
		if symbol.Kind != "function" {
			continue
		}
		linkerAddressText, ok := module.Symbols[symbol.Name]
		if !ok {
			continue
		}
		reviewedAddress, err := parseHex(symbol.Address, "reviewed symbol address")
		if err != nil {
			return fmt.Errorf("reviewed symbol %s: %w", symbol.Name, err)
		}
		linkerAddress, err := parseHex(linkerAddressText, "linker symbol address")
		if err != nil {
			return fmt.Errorf("module %s linker symbol %s: %w", module.ID, symbol.Name, err)
		}
		if reviewedAddress != linkerAddress {
			return fmt.Errorf("module %s reviewed symbol %s address %s disagrees with linker symbol address %s", module.ID, symbol.Name, symbol.Address, linkerAddressText)
		}
	}
	return nil
}

// sourceIdentifiers returns the C identifiers that appear as whole tokens in a
// source file.
//
// A symbol can only be referenced by an object if its name appears in that
// object's source, so this is a sound over-approximation of the externs a
// reconstruction actually needs. Dropping a genuinely needed symbol cannot
// corrupt the output: the link fails with an undefined reference.
func sourceIdentifiers(path string) (map[string]struct{}, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return nil, err
	}
	idents := make(map[string]struct{})
	start := -1
	isWord := func(c byte) bool {
		return c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')
	}
	for i := 0; i <= len(data); i++ {
		if i < len(data) && isWord(data[i]) {
			if start < 0 {
				start = i
			}
			continue
		}
		if start >= 0 {
			idents[string(data[start:i])] = struct{}{}
			start = -1
		}
	}
	return idents, nil
}

// compilerEmitted reports whether GCC can reference a symbol that never appears
// in the source text, so it must be provided regardless of what the source says.
//
// `__main` is the motivating case: GCC 2.6.3 emits a call to it in the prologue
// of `main()`. libgcc helpers are the same story -- an integer divide or a
// 64-bit shift becomes a call to `__divsi3` or `__ashldi3` with nothing in the
// source naming it -- and `memcpy`/`memset` appear from the `movstrsi` and
// block-clear expansions.
func compilerEmitted(name string) bool {
	if strings.HasPrefix(name, "__") {
		return true
	}
	switch name {
	case "memcpy", "memset", "memmove":
		return true
	}
	return false
}

func generateLinkerScript(buildRoot string, reconstruction configuredReconstruction, module linkerModuleSymbols) (string, error) {
	// Emit only the externs this source can actually reference.
	//
	// Providing every module symbol to every link is quadratic: with ~2,500
	// reconstructions and ~1,500 symbols per module it wrote and re-parsed 87 MB
	// of linker script per build, and got worse as either number grew. Filtering
	// by the identifiers present in the source removes almost all of it.
	used, err := sourceIdentifiers(reconstruction.code.sourcePath)
	if err != nil {
		return "", fmt.Errorf("read source for %s: %w", reconstruction.code.name, err)
	}

	bindings := make(map[string]string, len(module.Symbols))
	for name, address := range module.Symbols {
		if _, ok := used[name]; ok || compilerEmitted(name) {
			bindings[name] = address
		}
	}
	// Overrides are written for this reconstruction specifically, so they are
	// always emitted even if the name is reached through a macro.
	for name, address := range module.Overrides[reconstruction.code.name] {
		bindings[name] = address
	}
	names := make([]string, 0, len(bindings))
	for name := range bindings {
		names = append(names, name)
	}
	sort.Strings(names)
	var script strings.Builder
	script.WriteString("OUTPUT_ARCH(mips)\n")
	for _, name := range names {
		fmt.Fprintf(&script, "PROVIDE(%s = %s);\n", name, bindings[name])
	}
	script.WriteString("SECTIONS {\n")
	for _, extra := range reconstruction.ranges {
		if extra.section != ".rodata" {
			return "", fmt.Errorf("unsupported generated section %s", extra.section)
		}
		address := reconstruction.code.address
		if extra.start >= reconstruction.code.start {
			address += uint64(extra.start - reconstruction.code.start)
		} else {
			address -= uint64(reconstruction.code.start - extra.start)
		}
		fmt.Fprintf(&script, "  .rodata 0x%x : SUBALIGN(4) { *(.rodata) *(.rdata) }\n", address)
	}
	fmt.Fprintf(&script, "  .text 0x%x : SUBALIGN(4) { *(.text) }\n", reconstruction.code.address)
	script.WriteString("  /DISCARD/ : { *(.reginfo) *(.pdr) *(.comment) *(.gnu.attributes) }\n}\n")
	dir := filepath.Join(buildRoot, reconstruction.code.name)
	if err := os.MkdirAll(dir, 0o755); err != nil {
		return "", err
	}
	path := filepath.Join(dir, "generated.ld")
	if err := os.WriteFile(path, []byte(script.String()), 0o644); err != nil {
		return "", err
	}
	return path, nil
}
