package main

import (
	"crypto/sha256"
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"testing"
)

func validReconstructionConfig(t *testing.T) (modulesConfig, string, []byte) {
	t.Helper()
	root := t.TempDir()
	for _, path := range []string{"src/test.c"} {
		fullPath := filepath.Join(root, path)
		if err := os.MkdirAll(filepath.Dir(fullPath), 0o755); err != nil {
			t.Fatal(err)
		}
		if err := os.WriteFile(fullPath, []byte("test\n"), 0o600); err != nil {
			t.Fatal(err)
		}
	}
	target := make([]byte, 0x1000)
	config := modulesConfig{
		SchemaVersion: 1,
		TargetID:      "test-target",
		Modules: []moduleConfig{
			{
				ID: "main", DiscPath: "SCUS_942.21", Bytes: len(target),
				SHA256:         fmt.Sprintf("%x", sha256.Sum256(target)),
				Classification: "ps-x-exe", LoadAddress: "0x80010000",
				Reconstructions: []reconstructionConfig{
					{
						Symbol: "func_80010000", Address: "0x80010000",
						FileRange: "0x800-0x803", Bytes: 4,
						Language: "c", Status: "matching", Source: "src/test.c",
						CanonicalProfile: "gcc-2.6.3_O2_aspsx-2.34",
					},
				},
			},
		},
	}
	return config, root, target
}

func TestConfigureMainReconstructions(t *testing.T) {
	config, root, target := validReconstructionConfig(t)
	got, err := configureMainReconstructions(config, "test-target", root, target)
	if err != nil {
		t.Fatal(err)
	}
	if len(got) != 1 || got[0].code.start != 0x800 || got[0].code.end != 0x804 {
		t.Fatalf("unexpected configured reconstruction: %#v", got)
	}
}

func TestReconstructionTotals(t *testing.T) {
	config, _, _ := validReconstructionConfig(t)
	config.Modules[0].Reconstructions = append(config.Modules[0].Reconstructions,
		reconstructionConfig{Bytes: 8},
	)
	if got := reconstructionCount(config); got != 2 {
		t.Fatalf("reconstructionCount() = %d, want 2", got)
	}
	if got := reconstructionBytes(config); got != 12 {
		t.Fatalf("reconstructionBytes() = %d, want 12", got)
	}
}

func TestConfigureBattleReconstructions(t *testing.T) {
	config, root, target := validReconstructionConfig(t)
	target = make([]byte, 0x2000)
	config.Modules[0].ID = "battle"
	config.Modules[0].DiscPath = "BATTLE.BIN"
	config.Modules[0].Bytes = len(target)
	config.Modules[0].SHA256 = fmt.Sprintf("%x", sha256.Sum256(target))
	config.Modules[0].Classification = "raw-overlay"
	config.Modules[0].LoadAddress = "0x80067000"
	config.Modules[0].Reconstructions[0].Symbol = "func_800683c0"
	config.Modules[0].Reconstructions[0].Address = "0x800683c0"
	config.Modules[0].Reconstructions[0].FileRange = "0x13c0-0x13c3"

	got, err := configureModuleReconstructions(
		config, "test-target", "battle", "BATTLE.BIN", "raw-overlay", 0, root, target,
	)
	if err != nil {
		t.Fatal(err)
	}
	if len(got) != 1 || got[0].code.start != 0x13c0 || got[0].code.end != 0x13c4 {
		t.Fatalf("unexpected configured reconstruction: %#v", got)
	}
}

func TestConfigureReconstructionsSortsBeforeOverlapCheck(t *testing.T) {
	config, root, target := validReconstructionConfig(t)
	second := config.Modules[0].Reconstructions[0]
	second.Symbol = "func_80010004"
	second.Address = "0x80010004"
	second.FileRange = "0x804-0x807"
	config.Modules[0].Reconstructions = []reconstructionConfig{second, config.Modules[0].Reconstructions[0]}

	got, err := configureMainReconstructions(config, "test-target", root, target)
	if err != nil {
		t.Fatal(err)
	}
	if got[0].code.name != "func_80010000" || got[1].code.name != "func_80010004" {
		t.Fatalf("reconstructions were not sorted by file range: %#v", got)
	}
}

func TestConfigureMainReconstructionsRejectsInvalidMetadata(t *testing.T) {
	tests := []struct {
		name      string
		mutate    func(*modulesConfig)
		wantError string
	}{
		{
			name: "target identity",
			mutate: func(config *modulesConfig) {
				config.TargetID = "wrong-target"
			},
			wantError: "target_id",
		},
		{
			name: "target checksum",
			mutate: func(config *modulesConfig) {
				config.Modules[0].SHA256 = strings.Repeat("0", 64)
			},
			wantError: "SHA-256 mismatch",
		},
		{
			name: "range size",
			mutate: func(config *modulesConfig) {
				config.Modules[0].Reconstructions[0].Bytes = 3
			},
			wantError: "declares 3 bytes",
		},
		{
			name: "address mapping",
			mutate: func(config *modulesConfig) {
				config.Modules[0].Reconstructions[0].Address = "0x80010004"
			},
			wantError: "does not map",
		},
		{
			name: "compiler profile",
			mutate: func(config *modulesConfig) {
				config.Modules[0].Reconstructions[0].CanonicalProfile = "unknown"
			},
			wantError: "unsupported compiler profile",
		},
		{
			name: "instruction alignment",
			mutate: func(config *modulesConfig) {
				config.Modules[0].Reconstructions[0].Address = "0x80010001"
				config.Modules[0].Reconstructions[0].FileRange = "0x801-0x804"
			},
			wantError: "4-byte aligned",
		},
		{
			name: "path escape",
			mutate: func(config *modulesConfig) {
				config.Modules[0].Reconstructions[0].Source = "../outside.c"
			},
			wantError: "must stay inside",
		},
		{
			name: "overlap",
			mutate: func(config *modulesConfig) {
				reconstruction := config.Modules[0].Reconstructions[0]
				reconstruction.Symbol = "func_80010002"
				reconstruction.Address = "0x80010002"
				reconstruction.FileRange = "0x802-0x805"
				config.Modules[0].Reconstructions = append(config.Modules[0].Reconstructions, reconstruction)
			},
			wantError: "overlaps the previous reconstruction",
		},
		{
			name: "duplicate symbol",
			mutate: func(config *modulesConfig) {
				reconstruction := config.Modules[0].Reconstructions[0]
				reconstruction.Address = "0x80010004"
				reconstruction.FileRange = "0x804-0x807"
				config.Modules[0].Reconstructions = append(config.Modules[0].Reconstructions, reconstruction)
			},
			wantError: "duplicates symbol",
		},
	}
	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			config, root, target := validReconstructionConfig(t)
			test.mutate(&config)
			_, err := configureMainReconstructions(config, "test-target", root, target)
			if err == nil || !strings.Contains(err.Error(), test.wantError) {
				t.Fatalf("error = %v, want error containing %q", err, test.wantError)
			}
		})
	}
}

func TestParseInclusiveRange(t *testing.T) {
	start, end, err := parseInclusiveRange("0x31b84-0x31ba7")
	if err != nil {
		t.Fatal(err)
	}
	if start != 0x31b84 || end != 0x31ba8 {
		t.Fatalf("range = 0x%x-0x%x", start, end)
	}
	for _, value := range []string{"", "0x20", "0x20-0x10", "nope-0x20"} {
		if _, _, err := parseInclusiveRange(value); err == nil {
			t.Fatalf("parseInclusiveRange(%q) unexpectedly succeeded", value)
		}
	}
}

func TestCompilerProfiles(t *testing.T) {
	o0, ok := compilerProfileNamed("gcc-2.6.3_O0_aspsx-2.34")
	if !ok {
		t.Fatal("O0 profile is not registered")
	}
	o2, ok := compilerProfileNamed(canonicalProfileName)
	if !ok {
		t.Fatal("canonical O2 profile is not registered")
	}
	if o0.compilerPath != o2.compilerPath || o0.aspsxVersion != o2.aspsxVersion {
		t.Fatal("O0 profile must differ from O2 only by optimization")
	}
	if o0.optimization != "-O0" || o2.optimization != "-O2" {
		t.Fatalf("optimizations = %q, %q", o0.optimization, o2.optimization)
	}
	if _, ok := compilerProfileNamed("unknown"); ok {
		t.Fatal("unknown profile unexpectedly resolved")
	}
}

func TestValidateReconstructionSymbols(t *testing.T) {
	modules, _, _ := validReconstructionConfig(t)
	symbols := symbolsConfig{
		SchemaVersion: 1, TargetID: "test-target", ModuleID: "main",
		Symbols: []reviewedSymbol{
			{
				Name: "func_80010000", Address: "0x80010000", End: "0x80010004",
				Kind: "function", Ownership: "game", Confidence: "high",
			},
		},
	}
	if err := validateReconstructionSymbols(modules, symbols); err != nil {
		t.Fatal(err)
	}

	symbols.Symbols[0].End = "0x80010008"
	if err := validateReconstructionSymbols(modules, symbols); err == nil || !strings.Contains(err.Error(), "disagrees") {
		t.Fatalf("range mismatch error = %v", err)
	}
}

func TestValidateBattleReconstructionSymbols(t *testing.T) {
	modules, _, _ := validReconstructionConfig(t)
	modules.Modules[0].ID = "battle"
	modules.Modules[0].Reconstructions[0].Symbol = "func_800683c0"
	modules.Modules[0].Reconstructions[0].Address = "0x800683c0"
	symbols := symbolsConfig{
		SchemaVersion: 1, TargetID: "test-target", ModuleID: "battle",
		Symbols: []reviewedSymbol{
			{
				Name: "func_800683c0", Address: "0x800683c0", End: "0x800683c4",
				Kind: "function", Ownership: "game", Confidence: "high",
			},
		},
	}
	if err := validateReconstructionSymbols(modules, symbols); err != nil {
		t.Fatal(err)
	}
}

func TestValidateReviewedSymbolLinkerAddresses(t *testing.T) {
	symbols := symbolsConfig{
		ModuleID: "battle",
		Symbols: []reviewedSymbol{
			{Name: "open_active_unit_action_menu", Address: "0x8006f528", Kind: "function"},
			{Name: "reviewed_only", Address: "0x8006f600", Kind: "function"},
		},
	}
	module := linkerModuleSymbols{
		ID: "battle",
		Symbols: map[string]string{
			"open_active_unit_action_menu": "0x8006F528",
			"linker_only":                  "0x8006f700",
		},
	}
	if err := validateReviewedSymbolLinkerAddresses(symbols, module); err != nil {
		t.Fatal(err)
	}

	module.Symbols["open_active_unit_action_menu"] = "0x8006f52c"
	err := validateReviewedSymbolLinkerAddresses(symbols, module)
	if err == nil || !strings.Contains(err.Error(), "open_active_unit_action_menu") || !strings.Contains(err.Error(), "disagrees") {
		t.Fatalf("address mismatch error = %v", err)
	}
}

func TestValidateReviewedSymbolLinkerAddressesRejectsDifferentModules(t *testing.T) {
	symbols := symbolsConfig{ModuleID: "battle"}
	module := linkerModuleSymbols{ID: "main"}
	if err := validateReviewedSymbolLinkerAddresses(symbols, module); err == nil || !strings.Contains(err.Error(), "same module") {
		t.Fatalf("module mismatch error = %v", err)
	}
}

func TestValidateLibraryRanges(t *testing.T) {
	symbols := symbolsConfig{
		SchemaVersion: 1, TargetID: "test-target", ModuleID: "main",
		Symbols: []reviewedSymbol{
			{
				Name: "DrawSync", Address: "0x800246d4", End: "0x80024740",
				Kind: "function", Ownership: "psyq-library", Library: "libgpu", Confidence: "high",
			},
		},
	}
	libraries := librariesConfig{
		SchemaVersion: 1, TargetID: "test-target", ModuleID: "main",
		Ranges: []libraryRange{
			{
				ID: "libgpu", Address: "0x80022c24", End: "0x800275c0",
				Ownership: "psyq-library", Confidence: "high", Evidence: "test evidence",
			},
		},
	}
	if err := validateLibraryRanges(libraries, symbols); err != nil {
		t.Fatal(err)
	}

	symbols.Symbols[0].Library = "libgte"
	if err := validateLibraryRanges(libraries, symbols); err == nil || !strings.Contains(err.Error(), "unknown library") {
		t.Fatalf("unknown library error = %v", err)
	}

	symbols.Symbols[0].Library = "libgpu"
	symbols.Symbols[0].Address = "0x80028000"
	symbols.Symbols[0].End = "0x80028004"
	if err := validateLibraryRanges(libraries, symbols); err == nil || !strings.Contains(err.Error(), "outside") {
		t.Fatalf("out-of-range error = %v", err)
	}
}
