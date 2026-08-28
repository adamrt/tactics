package main

import (
	"crypto/sha256"
	"encoding/binary"
	"fmt"
	"os"
	"path/filepath"
	"strings"
	"testing"
)

func writeTestFile(t *testing.T, path string, data []byte) {
	t.Helper()
	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(path, data, 0o600); err != nil {
		t.Fatal(err)
	}
}

func candidateTestProject(t *testing.T) project {
	t.Helper()
	root := t.TempDir()
	mainTarget := make([]byte, 0x1000)
	battleTarget := make([]byte, 0x200)
	for index := range mainTarget {
		mainTarget[index] = byte(index)
	}
	for index := range battleTarget {
		battleTarget[index] = byte(index ^ 0x5a)
	}
	mainHash := fmt.Sprintf("%x", sha256.Sum256(mainTarget))
	battleHash := fmt.Sprintf("%x", sha256.Sum256(battleTarget))
	modules := fmt.Sprintf(`schema_version: 1
target_id: test
modules:
  - id: main
    disc_path: SCUS_942.21
    bytes: %d
    sha256: %q
    classification: ps-x-exe
    load_address: "0x80010000"
  - id: battle
    disc_path: BATTLE.BIN
    bytes: %d
    sha256: %q
    classification: raw-overlay
    load_address: "0x80067000"
`, len(mainTarget), mainHash, len(battleTarget), battleHash)
	writeTestFile(t, filepath.Join(root, "config", "modules.yaml"), []byte(modules))
	writeTestFile(t, filepath.Join(root, "build", "extracted", "files", "SCUS_942.21"), mainTarget)
	writeTestFile(t, filepath.Join(root, "build", "extracted", "files", "BATTLE.BIN"), battleTarget)
	return project{root: root, filesRoot: filepath.Join(root, "build", "extracted", "files")}
}

func TestResolveCandidateRangeUsesModuleAddressModel(t *testing.T) {
	p := candidateTestProject(t)
	mainCandidate, err := p.resolveCandidateRange("main", "func_80010020", "0x80010020", "0x80010030")
	if err != nil {
		t.Fatal(err)
	}
	if mainCandidate.FileStart != 0x820 || mainCandidate.FileEnd != 0x830 {
		t.Fatalf("main file range = 0x%x-0x%x", mainCandidate.FileStart, mainCandidate.FileEnd)
	}
	battleCandidate, err := p.resolveCandidateRange("battle", "func_80067020", "0x80067020", "0x80067030")
	if err != nil {
		t.Fatal(err)
	}
	if battleCandidate.FileStart != 0x20 || battleCandidate.FileEnd != 0x30 {
		t.Fatalf("battle file range = 0x%x-0x%x", battleCandidate.FileStart, battleCandidate.FileEnd)
	}
}

func TestResolveCandidateRangeRejectsInvalidInput(t *testing.T) {
	p := candidateTestProject(t)
	tests := []struct {
		name, module, symbol, start, end, want string
	}{
		{name: "module", module: "../battle", symbol: "func_80067020", start: "0x80067020", end: "0x80067030", want: "invalid module"},
		{name: "symbol", module: "battle", symbol: "bad/name", start: "0x80067020", end: "0x80067030", want: "invalid candidate symbol"},
		{name: "alignment", module: "battle", symbol: "func_80067020", start: "0x80067021", end: "0x80067030", want: "4-byte aligned"},
		{name: "reversed", module: "battle", symbol: "func_80067020", start: "0x80067030", end: "0x80067020", want: "nonempty"},
		{name: "outside", module: "battle", symbol: "func_80067200", start: "0x80067200", end: "0x80067204", want: "outside"},
	}
	for _, test := range tests {
		t.Run(test.name, func(t *testing.T) {
			_, err := p.resolveCandidateRange(test.module, test.symbol, test.start, test.end)
			if err == nil || !strings.Contains(err.Error(), test.want) {
				t.Fatalf("error = %v, want containing %q", err, test.want)
			}
		})
	}
}

func TestNormalizeM2CAssembly(t *testing.T) {
	assembly := []byte(`  alabel func_80079B14
func_80079B14:
    j func_80079B14
    jal func_801AD944
    lui $at, 0x8006
    addu $at, $at, $v0
    lw $v0, (0x800676A8 & 0xFFFF)($at)
    jr $v0
`)
	got := string(normalizeM2CAssembly(assembly, 0x80079a98, 0x8007a1d4))
	if strings.Contains(got, "alabel func_80079B14") || !strings.Contains(got, ".L80079B14:") || !strings.Contains(got, "j .L80079B14") {
		t.Fatalf("internal label was not normalized:\n%s", got)
	}
	if !strings.Contains(got, "jal func_801AD944") {
		t.Fatalf("external call was changed:\n%s", got)
	}
	if !strings.Contains(got, "%hi(jtbl_800676A8)") || !strings.Contains(got, "%lo(jtbl_800676A8)($at)") {
		t.Fatalf("jump table was not named for m2c:\n%s", got)
	}
}

func TestAppendM2CJumpTables(t *testing.T) {
	target := make([]byte, 0x40)
	binary.LittleEndian.PutUint32(target[0x10:], 0x80067020)
	binary.LittleEndian.PutUint32(target[0x14:], 0x8006702c)
	binary.LittleEndian.PutUint32(target[0x18:], 0x12345678)
	candidate := candidateRange{
		Module:       moduleConfig{ID: "battle", LoadAddress: "0x80067000", Classification: "raw-overlay"},
		RuntimeStart: 0x80067020, RuntimeEnd: 0x80067030, Target: target,
	}
	got, err := appendM2CJumpTables([]byte("/* 000020 80067020 00000000 */ nop\n/* 00002C 8006702C 00000000 */ nop\nlw $v0, %lo(jtbl_80067010)($at)\n"), candidate)
	if err != nil {
		t.Fatal(err)
	}
	for _, expected := range []string{".L80067020:", ".L8006702C:", "jtbl_80067010:", ".word .L80067020", ".word .L8006702C"} {
		if !strings.Contains(string(got), expected) {
			t.Fatalf("jump-table assembly does not contain %q:\n%s", expected, got)
		}
	}
	if strings.Contains(string(got), "12345678") {
		t.Fatalf("jump-table extraction did not stop outside candidate range:\n%s", got)
	}
}

func TestAsmDifferSettingsUsesPSXMIPSEndian(t *testing.T) {
	settings := asmDifferSettings("wip.bin")
	for _, expected := range []string{`"arch"] = "mipsel"`, `"myimg"] = "wip.bin"`, "mipsel-linux-gnu-objdump"} {
		if !strings.Contains(settings, expected) {
			t.Fatalf("settings do not contain %q:\n%s", expected, settings)
		}
	}
}

func TestResolveExplicitCandidateProfile(t *testing.T) {
	p := candidateTestProject(t)
	writeTestFile(t, filepath.Join(p.root, "wip", "candidate.c"), []byte("void candidate(void) {}\n"))
	writeTestFile(t, filepath.Join(p.root, "wip", "candidate.ld"), []byte("SECTIONS { .text 0x80067000 : { *(.text) } }\n"))
	baseArgs := []string{
		"build/extracted/files/BATTLE.BIN", "wip/candidate.c", "wip/candidate.ld", "0", "4",
	}

	candidate, err := p.resolveExplicitCandidate(baseArgs)
	if err != nil {
		t.Fatal(err)
	}
	if candidate.Profile != canonicalProfileName {
		t.Fatalf("default profile = %q", candidate.Profile)
	}

	candidate, err = p.resolveExplicitCandidate(append(baseArgs, "gcc-2.6.3_O0_aspsx-2.34"))
	if err != nil {
		t.Fatal(err)
	}
	if candidate.Profile != "gcc-2.6.3_O0_aspsx-2.34" {
		t.Fatalf("selected profile = %q", candidate.Profile)
	}

	if _, err := p.resolveExplicitCandidate(append(baseArgs, "unknown")); err == nil || !strings.Contains(err.Error(), "unsupported compiler profile") {
		t.Fatalf("unknown profile error = %v", err)
	}
}

func TestPermuterSettingsUsesR3000LittleEndianObjdump(t *testing.T) {
	settings := permuterSettings("func_801b47e0")
	for _, expected := range []string{`func_name = "func_801b47e0"`, `compiler_type = "gcc"`, `objdump_command = "mipsel-linux-gnu-objdump -drz -m mips:3000"`} {
		if !strings.Contains(settings, expected) {
			t.Fatalf("settings do not contain %q:\n%s", expected, settings)
		}
	}
}

func TestLinkerTextAddress(t *testing.T) {
	path := filepath.Join(t.TempDir(), "wip.ld")
	writeTestFile(t, path, []byte("OUTPUT_ARCH(mips)\nSECTIONS { .text 0x801b47e0 : { *(.text) } }\n"))
	address, err := linkerTextAddress(path)
	if err != nil {
		t.Fatal(err)
	}
	if address != 0x801b47e0 {
		t.Fatalf("address = 0x%x", address)
	}
}

func TestPermuterTemporaryPathRestriction(t *testing.T) {
	path := filepath.Join(t.TempDir(), "input.c")
	writeTestFile(t, path, []byte("void test(void) {}\n"))
	if err := temporaryPermuterPath(path, true); err != nil {
		t.Fatal(err)
	}
	if err := temporaryPermuterPath(filepath.Join(string(filepath.Separator), "outside.c"), false); err == nil {
		t.Fatal("path outside the temporary root was accepted")
	}
}
