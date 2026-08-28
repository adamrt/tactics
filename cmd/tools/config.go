// config.go loads and validates the target, module, symbol, and library metadata.
package main

import (
	"crypto/sha256"
	"errors"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strconv"
	"strings"

	"gopkg.in/yaml.v3"
)

const psxEXEHeaderSize = 0x800

type modulesConfig struct {
	SchemaVersion int            `yaml:"schema_version"`
	TargetID      string         `yaml:"target_id"`
	Modules       []moduleConfig `yaml:"modules"`
}

type moduleConfig struct {
	ID              string                 `yaml:"id"`
	DiscPath        string                 `yaml:"disc_path"`
	Bytes           int                    `yaml:"bytes"`
	SHA256          string                 `yaml:"sha256"`
	LBA             int                    `yaml:"lba"`
	Classification  string                 `yaml:"classification"`
	LoadAddress     string                 `yaml:"load_address"`
	Reconstructions []reconstructionConfig `yaml:"reconstructions"`
}

type candidatesConfig struct {
	SchemaVersion int               `yaml:"schema_version"`
	TargetID      string            `yaml:"target_id"`
	Candidates    []candidateConfig `yaml:"wip"`
}

type candidateConfig struct {
	Module           string `yaml:"module"`
	Symbol           string `yaml:"symbol"`
	Address          string `yaml:"address"`
	Status           string `yaml:"status"`
	Source           string `yaml:"source"`
	CanonicalProfile string `yaml:"canonical_profile"`
}

type reconstructionConfig struct {
	Symbol           string                `yaml:"symbol"`
	Address          string                `yaml:"address"`
	FileRange        string                `yaml:"file_range"`
	Bytes            int                   `yaml:"bytes"`
	Language         string                `yaml:"language"`
	Status           string                `yaml:"status"`
	Source           string                `yaml:"source"`
	CanonicalProfile string                `yaml:"canonical_profile"`
	VerifiedRanges   []verifiedRangeConfig `yaml:"verified_ranges"`
}

type verifiedRangeConfig struct {
	Section   string `yaml:"section"`
	Address   string `yaml:"address"`
	FileRange string `yaml:"file_range"`
	Bytes     int    `yaml:"bytes"`
}

type symbolsConfig struct {
	SchemaVersion int              `yaml:"schema_version"`
	TargetID      string           `yaml:"target_id"`
	ModuleID      string           `yaml:"module_id"`
	Symbols       []reviewedSymbol `yaml:"symbols"`
}

type librariesConfig struct {
	SchemaVersion int            `yaml:"schema_version"`
	TargetID      string         `yaml:"target_id"`
	ModuleID      string         `yaml:"module_id"`
	Ranges        []libraryRange `yaml:"ranges"`
}

type libraryRange struct {
	ID         string `yaml:"id"`
	Address    string `yaml:"address"`
	End        string `yaml:"end"`
	Ownership  string `yaml:"ownership"`
	Confidence string `yaml:"confidence"`
	Evidence   string `yaml:"evidence"`
}

type reviewedSymbol struct {
	Name       string `yaml:"name"`
	Address    string `yaml:"address"`
	End        string `yaml:"end"`
	Kind       string `yaml:"kind"`
	Ownership  string `yaml:"ownership"`
	Library    string `yaml:"library"`
	Confidence string `yaml:"confidence"`
}

type configuredReconstruction struct {
	code    codeRange
	profile compilerProfile
	ranges  []configuredVerifiedRange
}

type configuredVerifiedRange struct {
	section string
	start   int
	end     int
}

var compilerProfiles = map[string]compilerProfile{
	"gcc-2.6.3_O0_aspsx-2.34": {
		name: "gcc-2.6.3_O0_aspsx-2.34", compilerPath: "/opt/old-gcc/2.6.3-psx/cc1",
		optimization: "-O0", aspsxVersion: "2.34",
	},
	// Candidate profile under investigation. Several WORLD.BIN functions match
	// -O2 in structure but leave branch delay slots empty and do not strength-
	// reduce loop address arithmetic, which is the -O1 signature; -O0 is plainly
	// wrong for them (frame-pointer prologue, far larger). Registering the
	// profile is what makes it testable. Assign it per function and only on a
	// byte-exact match, exactly like the CARD -O0 and WLDCORE 2.21 exceptions --
	// its presence here is not a claim that any function uses it.
	"gcc-2.6.3_O1_aspsx-2.34": {
		name: "gcc-2.6.3_O1_aspsx-2.34", compilerPath: "/opt/old-gcc/2.6.3-psx/cc1",
		optimization: "-O1", aspsxVersion: "2.34",
	},
	"gcc-2.6.3_O2_aspsx-2.34": {
		name: "gcc-2.6.3_O2_aspsx-2.34", compilerPath: "/opt/old-gcc/2.6.3-psx/cc1",
		optimization: "-O2", aspsxVersion: "2.34",
	},
	// WORLD/WLDCORE.BIN and OPEN/OPEN.BIN were assembled with an ASPSX older
	// than 2.30, which expands an indexed global access to the four-instruction
	// `lui $at / addiu $at / addu $at / load 0($at)` form instead of folding
	// %lo into the load. See docs/compiler-toolchain.md.
	"gcc-2.6.3_O2_aspsx-2.21": {
		name: "gcc-2.6.3_O2_aspsx-2.21", compilerPath: "/opt/old-gcc/2.6.3-psx/cc1",
		optimization: "-O2", aspsxVersion: "2.21",
	},
}

func loadModulesConfig(path string) (modulesConfig, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return modulesConfig{}, err
	}
	var config modulesConfig
	if err := yaml.Unmarshal(data, &config); err != nil {
		return modulesConfig{}, fmt.Errorf("parse modules config: %w", err)
	}
	if config.SchemaVersion != 1 {
		return modulesConfig{}, fmt.Errorf("unsupported modules schema version %d", config.SchemaVersion)
	}
	if config.TargetID == "" {
		return modulesConfig{}, errors.New("modules config has no target_id")
	}
	return config, nil
}

func loadCandidatesConfig(path string) (candidatesConfig, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return candidatesConfig{}, err
	}
	var config candidatesConfig
	if err := yaml.Unmarshal(data, &config); err != nil {
		return candidatesConfig{}, fmt.Errorf("parse wip config: %w", err)
	}
	if config.SchemaVersion != 1 {
		return candidatesConfig{}, fmt.Errorf("unsupported candidates schema version %d", config.SchemaVersion)
	}
	if config.TargetID == "" {
		return candidatesConfig{}, errors.New("wip config has no target_id")
	}
	return config, nil
}

func loadSymbolsConfig(path string) (symbolsConfig, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return symbolsConfig{}, err
	}
	var config symbolsConfig
	if err := yaml.Unmarshal(data, &config); err != nil {
		return symbolsConfig{}, fmt.Errorf("parse symbols config: %w", err)
	}
	if config.SchemaVersion != 1 {
		return symbolsConfig{}, fmt.Errorf("unsupported symbols schema version %d", config.SchemaVersion)
	}
	if config.TargetID == "" || config.ModuleID == "" {
		return symbolsConfig{}, errors.New("symbols config is missing target_id or module_id")
	}
	return config, nil
}

func loadLibrariesConfig(path string) (librariesConfig, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return librariesConfig{}, err
	}
	var config librariesConfig
	if err := yaml.Unmarshal(data, &config); err != nil {
		return librariesConfig{}, fmt.Errorf("parse libraries config: %w", err)
	}
	if config.SchemaVersion != 1 {
		return librariesConfig{}, fmt.Errorf("unsupported libraries schema version %d", config.SchemaVersion)
	}
	if config.TargetID == "" || config.ModuleID == "" {
		return librariesConfig{}, errors.New("libraries config is missing target_id or module_id")
	}
	return config, nil
}

func validateLibraryRanges(libraries librariesConfig, symbols symbolsConfig) error {
	if libraries.TargetID != symbols.TargetID || libraries.ModuleID != symbols.ModuleID {
		return errors.New("library ranges do not describe the reviewed symbol target")
	}
	type parsedRange struct {
		libraryRange
		start uint64
		end   uint64
	}
	parsed := make(map[string]parsedRange)
	var previousEnd uint64
	for index, item := range libraries.Ranges {
		if !validSymbol(item.ID) || item.Confidence == "" || item.Evidence == "" {
			return fmt.Errorf("library range %d is missing valid identity or evidence", index+1)
		}
		if item.Ownership != "psyq-library" && item.Ownership != "c-runtime" {
			return fmt.Errorf("library range %s has invalid ownership %q", item.ID, item.Ownership)
		}
		if _, exists := parsed[item.ID]; exists {
			return fmt.Errorf("duplicate library range %s", item.ID)
		}
		start, err := parseHex(item.Address, "library address")
		if err != nil {
			return fmt.Errorf("library range %s: %w", item.ID, err)
		}
		end, err := parseHex(item.End, "library end")
		if err != nil {
			return fmt.Errorf("library range %s: %w", item.ID, err)
		}
		if start%4 != 0 || end%4 != 0 || end <= start || index > 0 && start < previousEnd {
			return fmt.Errorf("library range %s is invalid, overlapping, or out of order", item.ID)
		}
		parsed[item.ID] = parsedRange{libraryRange: item, start: start, end: end}
		previousEnd = end
	}
	for _, symbol := range symbols.Symbols {
		isLibrary := symbol.Ownership == "psyq-library" || symbol.Ownership == "c-runtime"
		if !isLibrary {
			if symbol.Library != "" {
				return fmt.Errorf("non-library symbol %s declares library %s", symbol.Name, symbol.Library)
			}
			continue
		}
		item, ok := parsed[symbol.Library]
		if !ok {
			return fmt.Errorf("library symbol %s has unknown library %q", symbol.Name, symbol.Library)
		}
		if item.Ownership != symbol.Ownership {
			return fmt.Errorf("library symbol %s ownership disagrees with %s", symbol.Name, item.ID)
		}
		start, _ := parseHex(symbol.Address, "symbol address")
		end, _ := parseHex(symbol.End, "symbol end")
		if start < item.start || end > item.end {
			return fmt.Errorf("library symbol %s lies outside %s", symbol.Name, item.ID)
		}
	}
	return nil
}

func validateReconstructionSymbols(modules modulesConfig, symbols symbolsConfig) error {
	if symbols.TargetID != modules.TargetID {
		return errors.New("reviewed symbols do not describe the configured module target")
	}
	byName := make(map[string]reviewedSymbol)
	var previousEnd uint64
	for index, symbol := range symbols.Symbols {
		if !validSymbol(symbol.Name) || symbol.Kind != "function" {
			return fmt.Errorf("reviewed symbol %d (%q) is not a valid function", index+1, symbol.Name)
		}
		if _, exists := byName[symbol.Name]; exists {
			return fmt.Errorf("duplicate reviewed symbol %s", symbol.Name)
		}
		address, err := parseHex(symbol.Address, "reviewed symbol address")
		if err != nil {
			return fmt.Errorf("reviewed symbol %s: %w", symbol.Name, err)
		}
		end, err := parseHex(symbol.End, "reviewed symbol end")
		if err != nil {
			return fmt.Errorf("reviewed symbol %s: %w", symbol.Name, err)
		}
		if address%4 != 0 || end%4 != 0 || end <= address {
			return fmt.Errorf("reviewed symbol %s has an invalid range", symbol.Name)
		}
		if index > 0 && address < previousEnd {
			return fmt.Errorf("reviewed symbol %s overlaps or is out of order", symbol.Name)
		}
		if symbol.Ownership == "" || symbol.Confidence == "" {
			return fmt.Errorf("reviewed symbol %s is missing ownership or confidence", symbol.Name)
		}
		byName[symbol.Name] = symbol
		previousEnd = end
	}

	var configuredModule *moduleConfig
	for index := range modules.Modules {
		if modules.Modules[index].ID != symbols.ModuleID {
			continue
		}
		if configuredModule != nil {
			return fmt.Errorf("modules config contains more than one %s module", symbols.ModuleID)
		}
		configuredModule = &modules.Modules[index]
	}
	if configuredModule == nil {
		return fmt.Errorf("modules config has no %s module", symbols.ModuleID)
	}
	for _, reconstruction := range configuredModule.Reconstructions {
		symbol, ok := byName[reconstruction.Symbol]
		if !ok {
			return fmt.Errorf("matching reconstruction %s has no reviewed symbol", reconstruction.Symbol)
		}
		address, err := parseHex(reconstruction.Address, "reconstruction address")
		if err != nil {
			return err
		}
		symbolAddress, _ := parseHex(symbol.Address, "reviewed symbol address")
		symbolEnd, _ := parseHex(symbol.End, "reviewed symbol end")
		if address != symbolAddress || symbolEnd-symbolAddress != uint64(reconstruction.Bytes) {
			return fmt.Errorf("matching reconstruction %s disagrees with its reviewed symbol range", reconstruction.Symbol)
		}
	}
	return nil
}

func compilerProfileNamed(name string) (compilerProfile, bool) {
	profile, ok := compilerProfiles[name]
	return profile, ok
}

func parseHex(value, field string) (uint64, error) {
	parsed, err := strconv.ParseUint(value, 0, 64)
	if err != nil {
		return 0, fmt.Errorf("invalid %s %q", field, value)
	}
	return parsed, nil
}

func parseInclusiveRange(value string) (int, int, error) {
	startText, endText, ok := strings.Cut(value, "-")
	if !ok {
		return 0, 0, fmt.Errorf("invalid file_range %q", value)
	}
	start, err := parseHex(startText, "file range start")
	if err != nil {
		return 0, 0, err
	}
	endInclusive, err := parseHex(endText, "file range end")
	if err != nil {
		return 0, 0, err
	}
	if endInclusive < start || endInclusive >= uint64(^uint(0)>>1) {
		return 0, 0, fmt.Errorf("invalid file_range %q", value)
	}
	return int(start), int(endInclusive + 1), nil
}

func validSymbol(symbol string) bool {
	if symbol == "" {
		return false
	}
	for index, char := range symbol {
		if char == '_' || char >= 'a' && char <= 'z' || char >= 'A' && char <= 'Z' || index > 0 && char >= '0' && char <= '9' {
			continue
		}
		return false
	}
	return true
}

func projectPath(root, value, field string) (string, error) {
	if value == "" {
		return "", fmt.Errorf("missing %s", field)
	}
	clean := filepath.Clean(filepath.FromSlash(value))
	if filepath.IsAbs(clean) || clean == ".." || strings.HasPrefix(clean, ".."+string(filepath.Separator)) {
		return "", fmt.Errorf("%s must stay inside the project: %q", field, value)
	}
	path := filepath.Join(root, clean)
	if info, err := os.Stat(path); err != nil {
		return "", fmt.Errorf("%s %q: %w", field, value, err)
	} else if !info.Mode().IsRegular() {
		return "", fmt.Errorf("%s is not a regular file: %q", field, value)
	}
	return path, nil
}

func configureModuleReconstructions(config modulesConfig, expectedTargetID, moduleID, expectedDiscPath, expectedClassification string, fileBias uint64, root string, target []byte) ([]configuredReconstruction, error) {
	if config.TargetID != expectedTargetID {
		return nil, fmt.Errorf("modules target_id %q does not match disc target_id %q", config.TargetID, expectedTargetID)
	}
	var configuredModule *moduleConfig
	for index := range config.Modules {
		if config.Modules[index].ID != moduleID {
			continue
		}
		if configuredModule != nil {
			return nil, fmt.Errorf("modules config contains more than one %s module", moduleID)
		}
		configuredModule = &config.Modules[index]
	}
	if configuredModule == nil {
		return nil, fmt.Errorf("modules config has no %s module", moduleID)
	}
	if configuredModule.DiscPath != expectedDiscPath || configuredModule.Classification != expectedClassification {
		return nil, fmt.Errorf("%s module must describe %s as %s", moduleID, expectedDiscPath, expectedClassification)
	}
	if configuredModule.Bytes != len(target) {
		return nil, fmt.Errorf("%s module byte count is %d, target has %d", moduleID, configuredModule.Bytes, len(target))
	}
	actualSHA256 := fmt.Sprintf("%x", sha256.Sum256(target))
	if !strings.EqualFold(configuredModule.SHA256, actualSHA256) {
		return nil, fmt.Errorf("%s module SHA-256 mismatch: got %s, expected %s", moduleID, actualSHA256, configuredModule.SHA256)
	}
	loadAddress, err := parseHex(configuredModule.LoadAddress, moduleID+" load_address")
	if err != nil {
		return nil, err
	}
	if len(configuredModule.Reconstructions) == 0 {
		return nil, fmt.Errorf("%s module has no reconstructions", moduleID)
	}

	reconstructions := append([]reconstructionConfig(nil), configuredModule.Reconstructions...)
	sort.SliceStable(reconstructions, func(i, j int) bool {
		left, _, leftErr := parseInclusiveRange(reconstructions[i].FileRange)
		right, _, rightErr := parseInclusiveRange(reconstructions[j].FileRange)
		return leftErr == nil && (rightErr != nil || left < right)
	})
	result := make([]configuredReconstruction, 0, len(reconstructions))
	previousEnd := 0
	seenSymbols := make(map[string]bool)
	for index, reconstruction := range reconstructions {
		label := fmt.Sprintf("reconstruction %d", index+1)
		if !validSymbol(reconstruction.Symbol) {
			return nil, fmt.Errorf("%s has invalid symbol %q", label, reconstruction.Symbol)
		}
		if seenSymbols[reconstruction.Symbol] {
			return nil, fmt.Errorf("%s duplicates symbol %s", label, reconstruction.Symbol)
		}
		seenSymbols[reconstruction.Symbol] = true
		if reconstruction.Language != "c" || reconstruction.Status != "matching" {
			return nil, fmt.Errorf("%s %s must be matching C", label, reconstruction.Symbol)
		}
		start, end, err := parseInclusiveRange(reconstruction.FileRange)
		if err != nil {
			return nil, fmt.Errorf("%s %s: %w", label, reconstruction.Symbol, err)
		}
		if start < previousEnd {
			return nil, fmt.Errorf("%s %s overlaps the previous reconstruction", label, reconstruction.Symbol)
		}
		if end > len(target) {
			return nil, fmt.Errorf("%s %s ends past the target executable", label, reconstruction.Symbol)
		}
		if reconstruction.Bytes != end-start {
			return nil, fmt.Errorf("%s %s declares %d bytes, range contains %d", label, reconstruction.Symbol, reconstruction.Bytes, end-start)
		}
		address, err := parseHex(reconstruction.Address, "runtime address")
		if err != nil {
			return nil, fmt.Errorf("%s %s: %w", label, reconstruction.Symbol, err)
		}
		if address < loadAddress || address-loadAddress+fileBias != uint64(start) {
			return nil, fmt.Errorf("%s %s address does not map to file range start 0x%x", label, reconstruction.Symbol, start)
		}
		if address%4 != 0 || start%4 != 0 || (end-start)%4 != 0 {
			return nil, fmt.Errorf("%s %s address and range must be 4-byte aligned", label, reconstruction.Symbol)
		}
		sourcePath, err := projectPath(root, reconstruction.Source, "source")
		if err != nil {
			return nil, fmt.Errorf("%s %s: %w", label, reconstruction.Symbol, err)
		}
		profileName := reconstruction.CanonicalProfile
		if profileName == "" {
			profileName = canonicalProfileName
		}
		profile, ok := compilerProfileNamed(profileName)
		if !ok {
			return nil, fmt.Errorf("%s %s uses unsupported compiler profile %q", label, reconstruction.Symbol, profileName)
		}
		configuredRanges := make([]configuredVerifiedRange, 0, len(reconstruction.VerifiedRanges))
		seenSections := make(map[string]bool)
		for _, extra := range reconstruction.VerifiedRanges {
			if extra.Section == "" || extra.Section == ".text" || seenSections[extra.Section] {
				return nil, fmt.Errorf("%s %s has invalid or duplicate verified section %q", label, reconstruction.Symbol, extra.Section)
			}
			seenSections[extra.Section] = true
			extraStart, extraEnd, err := parseInclusiveRange(extra.FileRange)
			if err != nil {
				return nil, fmt.Errorf("%s %s section %s: %w", label, reconstruction.Symbol, extra.Section, err)
			}
			if extraEnd > len(target) || extra.Bytes != extraEnd-extraStart {
				return nil, fmt.Errorf("%s %s section %s has an invalid target range", label, reconstruction.Symbol, extra.Section)
			}
			extraAddress, err := parseHex(extra.Address, "verified section address")
			if err != nil {
				return nil, fmt.Errorf("%s %s section %s: %w", label, reconstruction.Symbol, extra.Section, err)
			}
			if extraAddress < loadAddress || extraAddress-loadAddress+fileBias != uint64(extraStart) {
				return nil, fmt.Errorf("%s %s section %s address does not map to file range start 0x%x", label, reconstruction.Symbol, extra.Section, extraStart)
			}
			configuredRanges = append(configuredRanges, configuredVerifiedRange{section: extra.Section, start: extraStart, end: extraEnd})
		}
		result = append(result, configuredReconstruction{
			code: codeRange{
				name: reconstruction.Symbol, sourcePath: sourcePath,
				address: address, start: start, end: end,
			},
			profile: profile,
			ranges:  configuredRanges,
		})
		previousEnd = end
	}
	return result, nil
}

func configureMainReconstructions(config modulesConfig, expectedTargetID, root string, target []byte) ([]configuredReconstruction, error) {
	return configureModuleReconstructions(
		config, expectedTargetID, "main", "SCUS_942.21", "ps-x-exe",
		psxEXEHeaderSize, root, target,
	)
}
