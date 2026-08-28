// tools owns reproducible target-disc and binary-analysis operations.
package main

import (
	"bytes"
	"crypto/md5"  // #nosec G501 -- required ROM identity digest
	"crypto/sha1" // #nosec G505 -- required ROM identity digest
	"crypto/sha256"
	"debug/elf"
	"encoding/binary"
	"encoding/hex"
	"encoding/json"
	"encoding/xml"
	"errors"
	"fmt"
	"hash"
	"hash/crc32"
	"io"
	"os"
	"os/exec"
	"path/filepath"
	"runtime"
	"strconv"
	"strings"
	"sync"

	"gopkg.in/yaml.v3"
)

const expectedISOFileCount = 2464

type project struct {
	root          string
	configPath    string
	extractRoot   string
	filesRoot     string
	xmlPath       string
	inventoryPath string
}

type fileHashes struct {
	CRC32  string
	MD5    string
	SHA1   string
	SHA256 string
}

type discConfig struct {
	SchemaVersion int    `yaml:"schema_version"`
	TargetID      string `yaml:"target_id"`
	Input         struct {
		Path  string `yaml:"path"`
		Bytes int64  `yaml:"bytes"`
	} `yaml:"input"`
	Checksums fileHashes `yaml:"checksums"`
}

type isoProject struct {
	Tracks []isoTrack `xml:"track"`
}

type isoTrack struct {
	Directory isoDirectory `xml:"directory_tree"`
}

type isoDirectory struct {
	Files       []isoFile      `xml:"file"`
	Directories []isoDirectory `xml:"dir"`
}

type isoFile struct {
	Source string `xml:"source,attr"`
	LBA    string `xml:"offs,attr"`
	Type   string `xml:"type,attr"`
	Date   string `xml:"date,attr"`
}

type inventory struct {
	SchemaVersion int               `json:"schema_version"`
	TargetID      string            `json:"target_id"`
	Source        string            `json:"source"`
	FileCount     int               `json:"file_count"`
	Files         []inventoryRecord `json:"files"`
}

type inventoryRecord struct {
	Path         string `json:"path"`
	Bytes        int64  `json:"bytes"`
	SHA256       string `json:"sha256"`
	LBA          int    `json:"lba,omitempty"`
	Type         string `json:"type,omitempty"`
	Date         string `json:"date,omitempty"`
	Format       string `json:"format,omitempty"`
	EntryPoint   string `json:"entry_point,omitempty"`
	InitialGP    string `json:"initial_gp,omitempty"`
	TextAddress  string `json:"text_address,omitempty"`
	TextSize     int    `json:"text_size,omitempty"`
	DataAddress  string `json:"data_address,omitempty"`
	DataSize     int    `json:"data_size,omitempty"`
	BSSAddress   string `json:"bss_address,omitempty"`
	BSSSize      int    `json:"bss_size,omitempty"`
	StackAddress string `json:"stack_address,omitempty"`
	StackSize    int    `json:"stack_size,omitempty"`
}

func main() {
	if len(os.Args) < 2 {
		fatalf("usage: tools build [module]|wip <action> ...|check-config|extract|analyze|doctor")
	}
	commandsWithArguments := map[string]bool{
		"build":                  true,
		"wip":                    true,
		"check-config":           true,
		"extract":                true,
		"analyze":                true,
		"compile-permuter-input": true,
	}
	if !commandsWithArguments[os.Args[1]] && len(os.Args) != 2 {
		fatalf("usage: tools %s", os.Args[1])
	}
	p, err := findProject()
	if err != nil {
		fatalf("%v", err)
	}

	switch os.Args[1] {
	case "doctor":
		err = p.doctor()
	case "build":
		err = p.buildCommand(os.Args[2:])
	case "wip":
		err = p.candidateCommand(os.Args[2:])
	case "check-config", "extract", "analyze":
		err = p.toolsCommand(os.Args[1:])
	case "compile-permuter-input":
		err = p.compilePermuterInput(os.Args[2:])
	default:
		fatalf("unknown command %q", os.Args[1])
	}
	if err != nil {
		fatalf("%v", err)
	}
}

func fatalf(format string, args ...any) {
	fmt.Fprintf(os.Stderr, "tools: "+format+"\n", args...)
	os.Exit(1)
}

func findProject() (project, error) {
	dir, err := os.Getwd()
	if err != nil {
		return project{}, err
	}
	for {
		config := filepath.Join(dir, "config", "disc.yaml")
		if _, err := os.Stat(config); err == nil {
			extractRoot := filepath.Join(dir, "build", "extracted")
			return project{
				root:          dir,
				configPath:    config,
				extractRoot:   extractRoot,
				filesRoot:     filepath.Join(extractRoot, "files"),
				xmlPath:       filepath.Join(extractRoot, "disc.xml"),
				inventoryPath: filepath.Join(extractRoot, "inventory.json"),
			}, nil
		}
		parent := filepath.Dir(dir)
		if parent == dir {
			return project{}, errors.New("could not find config/disc.yaml")
		}
		dir = parent
	}
}

func (p project) loadConfig() (discConfig, error) {
	data, err := os.ReadFile(p.configPath)
	if err != nil {
		return discConfig{}, err
	}
	var config discConfig
	if err := yaml.Unmarshal(data, &config); err != nil {
		return discConfig{}, fmt.Errorf("parse disc config: %w", err)
	}
	if config.SchemaVersion != 1 || config.TargetID == "" || config.Input.Path == "" || config.Input.Bytes <= 0 || !validSHA256(config.Checksums.SHA256) {
		return discConfig{}, errors.New("disc config is incomplete or unsupported")
	}
	return config, nil
}

func streamHashes(path string) (fileHashes, error) {
	f, err := os.Open(path)
	if err != nil {
		return fileHashes{}, err
	}
	defer f.Close()

	crc := crc32.NewIEEE()
	md5sum := md5.New()   // #nosec G401 -- required ROM identity digest
	sha1sum := sha1.New() // #nosec G401 -- required ROM identity digest
	sha256sum := sha256.New()
	writers := []io.Writer{crc, md5sum, sha1sum, sha256sum}
	if _, err := io.Copy(io.MultiWriter(writers...), f); err != nil {
		return fileHashes{}, err
	}
	return fileHashes{
		CRC32:  digest(crc),
		MD5:    digest(md5sum),
		SHA1:   digest(sha1sum),
		SHA256: digest(sha256sum),
	}, nil
}

func digest(h hash.Hash) string {
	return hex.EncodeToString(h.Sum(nil))
}

func sha256File(path string) (string, error) {
	f, err := os.Open(path)
	if err != nil {
		return "", err
	}
	defer f.Close()
	h := sha256.New()
	if _, err := io.Copy(h, f); err != nil {
		return "", err
	}
	return digest(h), nil
}

func (p project) verifyDisc() (string, error) {
	config, err := p.loadConfig()
	if err != nil {
		return "", err
	}
	image := filepath.Join(p.root, filepath.FromSlash(config.Input.Path))
	info, err := os.Stat(image)
	if err != nil {
		return "", fmt.Errorf("missing target disc: %s", config.Input.Path)
	}
	expectedSize := config.Input.Bytes
	fmt.Printf("disc: %s\nbytes: %d\n", config.Input.Path, info.Size())
	if info.Size() != expectedSize {
		return "", fmt.Errorf("size mismatch: expected %d, got %d", expectedSize, info.Size())
	}

	actual, err := streamHashes(image)
	if err != nil {
		return "", err
	}
	checks := []struct{ name, value string }{
		{"crc32", actual.CRC32}, {"md5", actual.MD5}, {"sha1", actual.SHA1}, {"sha256", actual.SHA256},
	}
	failed := false
	for _, check := range checks {
		expected := strings.ToLower(map[string]string{"crc32": config.Checksums.CRC32, "md5": config.Checksums.MD5, "sha1": config.Checksums.SHA1, "sha256": config.Checksums.SHA256}[check.name])
		state := "ok"
		if check.value != expected {
			state, failed = "MISMATCH", true
		}
		fmt.Printf("%s: %s [%s]\n", check.name, check.value, state)
	}
	if failed {
		return "", errors.New("target disc verification failed")
	}
	return image, nil
}

func readISOProject(path string) (isoProject, error) {
	data, err := os.ReadFile(path)
	if err != nil {
		return isoProject{}, err
	}
	var project isoProject
	return project, xml.Unmarshal(data, &project)
}

func flattenFiles(dir isoDirectory, output *[]isoFile) {
	*output = append(*output, dir.Files...)
	for _, child := range dir.Directories {
		flattenFiles(child, output)
	}
}

func (p project) validExtraction() bool {
	if _, err := os.Stat(filepath.Join(p.filesRoot, "SCUS_942.21")); err != nil {
		return false
	}
	project, err := readISOProject(p.xmlPath)
	if err != nil {
		return false
	}
	var files []isoFile
	for _, track := range project.Tracks {
		flattenFiles(track.Directory, &files)
	}
	return len(files) == expectedISOFileCount
}

func (p project) extractDisc() error {
	image, err := p.verifyDisc()
	if err != nil {
		return err
	}
	if p.validExtraction() {
		fmt.Printf("extraction already complete: %s\n", filepath.Join("build", "extracted"))
		return p.buildInventory()
	}
	if _, err := os.Stat(p.extractRoot); err == nil {
		return fmt.Errorf("incomplete extraction exists at build/extracted; move or remove it before retrying")
	} else if !os.IsNotExist(err) {
		return err
	}
	if err := os.MkdirAll(p.filesRoot, 0o755); err != nil {
		return err
	}
	cmd := exec.Command("dumpsxiso", dumpsxisoArgs(p.filesRoot, p.xmlPath, image)...)
	cmd.Dir, cmd.Stdout, cmd.Stderr = p.root, os.Stdout, os.Stderr
	if err := cmd.Run(); err != nil {
		if cleanupErr := os.RemoveAll(p.extractRoot); cleanupErr != nil {
			return fmt.Errorf("dumpsxiso: %w; cleanup failed: %v", err, cleanupErr)
		}
		return fmt.Errorf("dumpsxiso: %w", err)
	}
	if !p.validExtraction() {
		if err := os.RemoveAll(p.extractRoot); err != nil {
			return fmt.Errorf("dumpsxiso finished without producing the expected extraction; cleanup failed: %w", err)
		}
		return errors.New("dumpsxiso finished without producing the expected extraction")
	}
	fmt.Printf("extracted %d ISO files to build/extracted/files\n", expectedISOFileCount)
	return p.buildInventory()
}

func dumpsxisoArgs(filesRoot, xmlPath, input string) []string {
	return []string{"--quiet", "--lba", "-x", filesRoot, "-s", xmlPath, input}
}

func psxEXEMetadata(path string) (inventoryRecord, bool, error) {
	f, err := os.Open(path)
	if err != nil {
		return inventoryRecord{}, false, err
	}
	defer f.Close()
	header := make([]byte, 0x38)
	if _, err := io.ReadFull(f, header); err != nil {
		if errors.Is(err, io.EOF) || errors.Is(err, io.ErrUnexpectedEOF) {
			return inventoryRecord{}, false, nil
		}
		return inventoryRecord{}, false, err
	}
	if string(header[:8]) != "PS-X EXE" {
		return inventoryRecord{}, false, nil
	}
	word := func(offset int) uint32 { return binary.LittleEndian.Uint32(header[offset : offset+4]) }
	hex32 := func(value uint32) string { return fmt.Sprintf("0x%08x", value) }
	return inventoryRecord{
		Format: "ps-x-exe", EntryPoint: hex32(word(0x10)), InitialGP: hex32(word(0x14)),
		TextAddress: hex32(word(0x18)), TextSize: int(word(0x1c)),
		DataAddress: hex32(word(0x20)), DataSize: int(word(0x24)),
		BSSAddress: hex32(word(0x28)), BSSSize: int(word(0x2c)),
		StackAddress: hex32(word(0x30)), StackSize: int(word(0x34)),
	}, true, nil
}

func (p project) buildInventory() error {
	if !p.validExtraction() {
		return errors.New("run `make bootstrap` first")
	}
	projectXML, err := readISOProject(p.xmlPath)
	if err != nil {
		return err
	}
	var files []isoFile
	for _, track := range projectXML.Tracks {
		flattenFiles(track.Directory, &files)
	}
	records := make([]inventoryRecord, 0, len(files))
	for _, file := range files {
		path, relative, err := extractionSourcePath(p.filesRoot, p.extractRoot, file.Source)
		if err != nil {
			return fmt.Errorf("disc.xml source %q: %w", file.Source, err)
		}
		info, err := os.Stat(path)
		if err != nil {
			return fmt.Errorf("disc.xml source %q: %w", file.Source, err)
		}
		sum, err := sha256File(path)
		if err != nil {
			return err
		}
		record := inventoryRecord{Path: filepath.ToSlash(relative), Bytes: info.Size(), SHA256: sum, Type: file.Type, Date: file.Date}
		if file.LBA != "" {
			record.LBA, err = strconv.Atoi(file.LBA)
			if err != nil {
				return fmt.Errorf("invalid LBA %q for %s", file.LBA, file.Source)
			}
		}
		if metadata, ok, err := psxEXEMetadata(path); err != nil {
			return err
		} else if ok {
			metadata.Path, metadata.Bytes, metadata.SHA256 = record.Path, record.Bytes, record.SHA256
			metadata.LBA, metadata.Type, metadata.Date = record.LBA, record.Type, record.Date
			record = metadata
		}
		records = append(records, record)
	}
	config, err := p.loadConfig()
	if err != nil {
		return err
	}
	payload := inventory{SchemaVersion: 1, TargetID: config.TargetID, Source: "build/extracted/disc.xml", FileCount: len(records), Files: records}
	data, err := json.MarshalIndent(payload, "", "  ")
	if err != nil {
		return err
	}
	data = append(data, '\n')
	if err := os.WriteFile(p.inventoryPath, data, 0o644); err != nil {
		return err
	}
	fmt.Printf("wrote %d records to build/extracted/inventory.json\n", len(records))
	return p.buildAnalysis()
}

func extractionSourcePath(filesRoot, extractRoot, source string) (string, string, error) {
	path := filepath.FromSlash(source)
	if !filepath.IsAbs(path) {
		path = filepath.Join(extractRoot, path)
	}
	relative, err := filepath.Rel(filesRoot, path)
	if err != nil {
		return "", "", err
	}
	if relative == ".." || strings.HasPrefix(relative, ".."+string(filepath.Separator)) || filepath.IsAbs(relative) {
		return "", "", errors.New("path is outside the extracted files directory")
	}
	return path, relative, nil
}

func (p project) doctor() error {
	fmt.Printf("go: %s\nplatform: %s/%s\n", runtime.Version(), runtime.GOOS, runtime.GOARCH)
	commands := []struct {
		name   string
		banner string
	}{
		{"dumpsxiso", "DUMPSXISO 2.30"},
		{"mkpsxiso", "MKPSXISO 2.30"},
		{"mipsel-linux-gnu-as", ""},
		{"mipsel-linux-gnu-cpp", ""},
		{"mipsel-linux-gnu-gcc", ""},
		{"python3", ""},
		{"qemu-i386", ""},
		{"file", ""},
	}
	for _, command := range commands {
		path, err := exec.LookPath(command.name)
		if err != nil {
			return fmt.Errorf("missing required command: %s", command.name)
		}
		if command.banner != "" {
			output, err := exec.Command(path, "--help").CombinedOutput()
			if err != nil || !bytes.Contains(output, []byte(command.banner)) {
				return fmt.Errorf("%s is not the required version: expected %s", command.name, command.banner)
			}
		}
		fmt.Printf("%s: %s\n", command.name, path)
	}
	for _, path := range []string{
		"/opt/old-gcc/2.6.3-psx/cc1",
		"/opt/maspsx/maspsx.py",
	} {
		if _, err := os.Stat(path); err != nil {
			return fmt.Errorf("missing required tool: %s", path)
		}
		fmt.Printf("tool: %s\n", path)
	}
	return nil
}

type compilerProfile struct {
	name         string
	compilerPath string
	aspsxVersion string
	optimization string
}

type codeRange struct {
	name       string
	address    uint64
	sourcePath string
	start      int
	end        int
}

func runInDir(dir string, arguments ...string) error {
	cmd := exec.Command(arguments[0], arguments[1:]...)
	cmd.Dir, cmd.Stdout, cmd.Stderr = dir, os.Stdout, os.Stderr
	if err := cmd.Run(); err != nil {
		return fmt.Errorf("%s: %w", arguments[0], err)
	}
	return nil
}

func transformFile(dir, input, output string, arguments ...string) error {
	in, err := os.Open(input)
	if err != nil {
		return err
	}
	defer in.Close()
	out, err := os.Create(output)
	if err != nil {
		return err
	}
	cmd := exec.Command(arguments[0], arguments[1:]...)
	cmd.Dir, cmd.Stdin, cmd.Stdout, cmd.Stderr = dir, in, out, os.Stderr
	if err := cmd.Run(); err != nil {
		out.Close()
		return fmt.Errorf("%s: %w", arguments[0], err)
	}
	return out.Close()
}

func mismatch(expected, actual []byte) (int, bool) {
	limit := min(len(expected), len(actual))
	for offset := range limit {
		if expected[offset] != actual[offset] {
			return offset, true
		}
	}
	if len(expected) != len(actual) {
		return limit, true
	}
	return 0, false
}

func instructionDifference(expected, actual []byte, offset int) string {
	instructionOffset := offset &^ 3
	wordAt := func(code []byte) string {
		if instructionOffset+4 > len(code) {
			return "<truncated>"
		}
		return fmt.Sprintf("0x%08x", binary.LittleEndian.Uint32(code[instructionOffset:]))
	}
	return fmt.Sprintf("instruction +0x%x: expected %s, got %s", instructionOffset, wordAt(expected), wordAt(actual))
}

func (p project) compileHistoricalC(sourcePath, linkPath, buildDir string, profile compilerProfile) ([]byte, error) {
	sections, err := p.compileHistoricalSections(sourcePath, linkPath, buildDir, profile)
	if err != nil {
		return nil, err
	}
	return sections[".text"], nil
}

func (p project) compileHistoricalSections(sourcePath, linkPath, buildDir string, profile compilerProfile) (map[string][]byte, error) {
	if err := os.MkdirAll(buildDir, 0o755); err != nil {
		return nil, err
	}
	assembly := filepath.Join(buildDir, profile.name+".s")
	preprocessed := filepath.Join(buildDir, profile.name+".i")
	translated := filepath.Join(buildDir, profile.name+".maspsx.s")
	object := filepath.Join(buildDir, profile.name+".o")
	binaryInput := object
	binary := filepath.Join(buildDir, profile.name+".bin")
	cpp := []string{
		"mipsel-linux-gnu-cpp", "-P", "-undef", "-nostdinc", "-Iinclude",
		sourcePath, "-o", preprocessed,
	}
	if err := runInDir(p.root, cpp...); err != nil {
		return nil, err
	}
	cacheKey, err := compilationCacheKey(preprocessed, linkPath, profile)
	if err != nil {
		return nil, err
	}
	cachePath := filepath.Join(p.root, "build", "cache", "tools", cacheKey+".json")
	if os.Getenv("TOOLS_CACHE") != "0" {
		if data, err := os.ReadFile(cachePath); err == nil {
			var sections map[string][]byte
			if json.Unmarshal(data, &sections) == nil && sections[".text"] != nil {
				return sections, nil
			}
		}
	}
	cc1 := []string{
		"qemu-i386", profile.compilerPath, preprocessed, "-o", assembly,
		"-G0", "-w", "-funsigned-char", "-fpeephole", "-ffunction-cse",
		"-fpcc-struct-return", "-fcommon", "-fverbose-asm", "-msoft-float",
		"-quiet", "-mcpu=3000", "-fgnu-linker", "-mgas", "-gcoff", profile.optimization,
	}
	if err := runInDir(p.root, cc1...); err != nil {
		return nil, err
	}
	if err := transformFile(p.root, assembly, translated, "python3", "/opt/maspsx/maspsx.py", "--aspsx-version="+profile.aspsxVersion); err != nil {
		return nil, err
	}
	if err := runInDir(p.root, "mipsel-linux-gnu-as", "-EL", "-march=r3000", "-mtune=r3000", "-no-pad-sections", "-O1", "-G0", "-o", object, translated); err != nil {
		return nil, err
	}
	if linkPath != "" {
		elf := filepath.Join(buildDir, profile.name+".elf")
		if err := runInDir(p.root, "mipsel-linux-gnu-ld", "-EL", "-T", linkPath, "-o", elf, object); err != nil {
			return nil, err
		}
		binaryInput = elf
	}
	if err := runInDir(p.root, "mipsel-linux-gnu-objcopy", "-O", "binary", "--only-section=.text", binaryInput, binary); err != nil {
		return nil, err
	}
	text, err := os.ReadFile(binary)
	if err != nil {
		return nil, err
	}
	sections := map[string][]byte{".text": text}
	if linkPath == "" {
		return sections, nil
	}
	linked, err := elf.Open(binaryInput)
	if err != nil {
		return nil, err
	}
	defer linked.Close()
	for _, section := range linked.Sections {
		if section.Size == 0 || section.Flags&elf.SHF_ALLOC == 0 || section.Name == ".text" || section.Name == ".MIPS.abiflags" {
			continue
		}
		if section.Type == elf.SHT_NOBITS {
			sections[section.Name] = nil
			continue
		}
		data, err := section.Data()
		if err != nil {
			return nil, fmt.Errorf("read linked section %s: %w", section.Name, err)
		}
		sections[section.Name] = data
	}
	if os.Getenv("TOOLS_CACHE") != "0" {
		if err := os.MkdirAll(filepath.Dir(cachePath), 0o755); err != nil {
			return nil, err
		}
		data, err := json.Marshal(sections)
		if err != nil {
			return nil, err
		}
		if err := os.WriteFile(cachePath, data, 0o644); err != nil {
			return nil, err
		}
	}
	return sections, nil
}

var toolDigestCache sync.Map

func toolDigest(path string) (string, error) {
	if value, ok := toolDigestCache.Load(path); ok {
		return value.(string), nil
	}
	digest, err := sha256File(path)
	if err != nil {
		return "", err
	}
	toolDigestCache.Store(path, digest)
	return digest, nil
}

func compilationCacheKey(preprocessed, linkPath string, profile compilerProfile) (string, error) {
	hash := sha256.New()
	hash.Write([]byte("tools-historical-pipeline-v1\x00" + profile.name + "\x00" + profile.optimization + "\x00" + profile.aspsxVersion + "\x00"))
	for _, path := range []string{profile.compilerPath, "/opt/maspsx/maspsx.py"} {
		digest, err := toolDigest(path)
		if err != nil {
			return "", err
		}
		hash.Write([]byte(digest))
	}
	for _, path := range []string{preprocessed, linkPath} {
		if path == "" {
			continue
		}
		data, err := os.ReadFile(path)
		if err != nil {
			return "", err
		}
		hash.Write(data)
	}
	return hex.EncodeToString(hash.Sum(nil)), nil
}

// matchCandidate compiles a prospective reconstruction without adding it to the
// reviewed manifest. It is intentionally limited to project-local inputs so
// experiments use the same pinned toolchain and leave production metadata alone.
func (p project) matchCandidate(args []string) error {
	candidate, err := p.resolveExplicitCandidate(args)
	if err != nil {
		return fmt.Errorf("usage: tools wip match <target> <source> <linker-script> <file-offset> <bytes> [profile]: %w", err)
	}
	compiled, profile, err := p.compileExplicitCandidate(candidate)
	if err != nil {
		return err
	}
	if offset, differs := mismatch(candidate.Expected, compiled); differs {
		return fmt.Errorf("wip %s differs at function offset 0x%x (file offset 0x%x; expected %d bytes, got %d; %s); run make wip ACTION=diff with the same TARGET/SOURCE/LINKER/OFFSET/BYTES values", candidate.SourceArg, offset, candidate.Start+uint64(offset), len(candidate.Expected), len(compiled), instructionDifference(candidate.Expected, compiled, offset))
	}
	fmt.Printf("matching WIP: %s (%d bytes, profile %s)\n", candidate.SourceArg, len(compiled), profile.name)
	return nil
}

func replaceRange(image []byte, start, end int, replacement []byte) error {
	if start < 0 || end < start || end > len(image) {
		return fmt.Errorf("invalid replacement range 0x%x-0x%x for %d-byte image", start, end, len(image))
	}
	if len(replacement) != end-start {
		return fmt.Errorf("replacement is %d bytes, range requires %d", len(replacement), end-start)
	}
	copy(image[start:end], replacement)
	return nil
}

func (p project) buildMain() error {
	input := filepath.Join(p.filesRoot, "SCUS_942.21")
	want, err := os.ReadFile(input)
	if err != nil {
		return errors.New("run `make bootstrap` first")
	}
	config, err := loadModulesConfig(filepath.Join(p.root, "config", "modules.yaml"))
	if err != nil {
		return err
	}
	symbols, err := loadSymbolsConfig(filepath.Join(p.root, "config", "main-symbols.yaml"))
	if err != nil {
		return err
	}
	libraries, err := loadLibrariesConfig(filepath.Join(p.root, "config", "libraries.yaml"))
	if err != nil {
		return err
	}
	if err := validateReconstructionSymbols(config, symbols); err != nil {
		return err
	}
	if err := validateLibraryRanges(libraries, symbols); err != nil {
		return err
	}
	return p.buildConfiguredModule(
		config, symbols, want, "main", "SCUS_942.21", "ps-x-exe", psxEXEHeaderSize,
		filepath.Join(p.root, "build", "main"), "scus_942.21", "main executable",
	)
}

func (p project) buildBattle() error {
	return p.buildRawOverlay("battle", "BATTLE.BIN", "battle-symbols.yaml", "battle", "battle.bin", "BATTLE overlay")
}

func moduleBuildOutput(root string, module moduleConfig) string {
	base := strings.ToLower(filepath.Base(filepath.FromSlash(module.DiscPath)))
	if module.ID == "main" {
		return filepath.Join(root, "build", "main", base)
	}
	if module.ID == "battle" {
		return filepath.Join(root, "build", "battle", base)
	}
	if module.ID == "battle" {
		return filepath.Join(root, "build", "battle", base)
	}
	if strings.HasPrefix(module.ID, "event-") && module.ID != "event-small" {
		name := strings.TrimSuffix(base, filepath.Ext(base))
		return filepath.Join(root, "build", "event", name, base)
	}
	return filepath.Join(root, "build", strings.ToLower(filepath.Dir(filepath.FromSlash(module.DiscPath))), base)
}

func (p project) buildModule(module moduleConfig, config modulesConfig) (string, error) {
	want, err := os.ReadFile(filepath.Join(p.filesRoot, filepath.FromSlash(module.DiscPath)))
	if err != nil {
		return "", errors.New("run `make bootstrap` first")
	}
	symbols, err := p.reviewedSymbolsForModule(module.ID)
	if err != nil {
		return "", err
	}
	if err := validateReconstructionSymbols(config, symbols); err != nil {
		return "", err
	}
	if module.ID == "main" {
		libraries, err := loadLibrariesConfig(filepath.Join(p.root, "config", "libraries.yaml"))
		if err != nil {
			return "", err
		}
		if err := validateLibraryRanges(libraries, symbols); err != nil {
			return "", err
		}
	}
	bias, err := moduleFileBias(module.Classification)
	if err != nil {
		return "", err
	}
	output := moduleBuildOutput(p.root, module)
	label := module.DiscPath
	if err := p.buildConfiguredModule(config, symbols, want, module.ID, module.DiscPath, module.Classification, bias, filepath.Dir(output), filepath.Base(output), label); err != nil {
		return "", err
	}
	return output, nil
}

var buildModuleAliases = map[string]string{
	"main":      "main",
	"battle":    "battle",
	"attack":    "event-attack",
	"card":      "event-card",
	"debugchr":  "event-debugchr",
	"equip":     "event-equip",
	"etc":       "event-etc",
	"effect259": "effect-e259",
	"helpmenu":  "event-helpmenu",
	"jobstts":   "event-jobstts",
	"option":    "event-option",
	"opening":   "opening",
	"require":   "event-require",
	"bunit":     "event-bunit",
	"small":     "event-small",
	"wldcore":   "wldcore",
	"world":     "world",
}

func (p project) buildCommand(args []string) error {
	if len(args) > 1 {
		return errors.New("usage: tools build [main|battle|attack|card|debugchr|effect259|equip|etc|helpmenu|jobstts|opening|option|require|bunit|small|wldcore|world|disc]")
	}
	name := "disc"
	if len(args) == 1 && args[0] != "" {
		name = args[0]
	}
	if name == "all" || name == "disc" {
		return p.buildDisc()
	}
	moduleID, ok := buildModuleAliases[name]
	if !ok {
		return fmt.Errorf("unknown build module %q; choose main, battle, attack, card, debugchr, effect259, equip, etc, helpmenu, jobstts, opening, option, require, bunit, small, wldcore, world, or disc", name)
	}
	if err := p.checkConfig(); err != nil {
		return err
	}
	modules, err := loadModulesConfig(filepath.Join(p.root, "config", "modules.yaml"))
	if err != nil {
		return err
	}
	for _, module := range modules.Modules {
		if module.ID != moduleID {
			continue
		}
		if len(module.Reconstructions) == 0 {
			return fmt.Errorf("module %s has no matching reconstructions", moduleID)
		}
		_, err := p.buildModule(module, modules)
		return err
	}
	return fmt.Errorf("modules config has no module %s", moduleID)
}

func (p project) buildRawOverlay(moduleID, discPath, symbolsFile, buildSubdir, outputName, label string) error {
	input := filepath.Join(p.filesRoot, filepath.FromSlash(discPath))
	want, err := os.ReadFile(input)
	if err != nil {
		return errors.New("run `make bootstrap` first")
	}
	config, err := loadModulesConfig(filepath.Join(p.root, "config", "modules.yaml"))
	if err != nil {
		return err
	}
	symbols, err := loadSymbolsConfig(filepath.Join(p.root, "config", symbolsFile))
	if err != nil {
		return err
	}
	if err := validateReconstructionSymbols(config, symbols); err != nil {
		return err
	}
	return p.buildConfiguredModule(
		config, symbols, want, moduleID, discPath, "raw-overlay", 0,
		filepath.Join(p.root, "build", filepath.FromSlash(buildSubdir)), outputName, label,
	)
}

func (p project) buildConfiguredModule(config modulesConfig, symbols symbolsConfig, want []byte, moduleID, discPath, classification string, fileBias uint64, buildDir, outputName, label string) error {
	discConfig, err := p.loadConfig()
	if err != nil {
		return err
	}
	linkers, err := loadLinkerSymbolsConfig(filepath.Join(p.root, "config", "linker-symbols.yaml"))
	if err != nil {
		return err
	}
	linkModule, err := linkers.module(moduleID)
	if err != nil {
		return err
	}
	if err := validateReviewedSymbolLinkerAddresses(symbols, linkModule); err != nil {
		return err
	}
	reconstructions, err := configureModuleReconstructions(
		config, discConfig.TargetID, moduleID, discPath, classification, fileBias, p.root, want,
	)
	if err != nil {
		return err
	}
	got := append([]byte(nil), want...)
	matchedBytes := 0
	matchedOffsets := make([]bool, len(want))
	countMatched := func(start, end int) {
		for offset := start; offset < end; offset++ {
			if !matchedOffsets[offset] {
				matchedOffsets[offset] = true
				matchedBytes++
			}
		}
	}
	type compileResult struct {
		sections map[string][]byte
		err      error
	}
	results := make([]compileResult, len(reconstructions))
	jobs := 4
	if value := os.Getenv("TOOLS_JOBS"); value != "" {
		parsed, err := strconv.Atoi(value)
		if err != nil || parsed < 1 {
			return fmt.Errorf("invalid TOOLS_JOBS %q", value)
		}
		jobs = parsed
	}
	work := make(chan int)
	var workers sync.WaitGroup
	for range min(jobs, len(reconstructions)) {
		workers.Add(1)
		go func() {
			defer workers.Done()
			for index := range work {
				reconstruction := reconstructions[index]
				generatedLinker, err := generateLinkerScript(buildDir, reconstruction, linkModule)
				if err != nil {
					results[index].err = fmt.Errorf("generate linker for %s: %w", reconstruction.code.name, err)
					continue
				}
				results[index].sections, results[index].err = p.compileHistoricalSections(reconstruction.code.sourcePath, generatedLinker, filepath.Join(buildDir, reconstruction.code.name), reconstruction.profile)
			}
		}()
	}
	for index := range reconstructions {
		work <- index
	}
	close(work)
	workers.Wait()
	var mismatched []string
	for index, reconstruction := range reconstructions {
		if results[index].err != nil {
			return fmt.Errorf("compile %s: %w", reconstruction.code.name, results[index].err)
		}
		compiledSections := results[index].sections
		compiled := compiledSections[".text"]
		expected := want[reconstruction.code.start:reconstruction.code.end]
		if offset, differs := mismatch(expected, compiled); differs {
			// Report every mismatching function rather than only the first.
			// Fail-fast turns "which reconstructions regressed?" into one full
			// build per answer, which is unusable after a bulk change.
			// TOOLS_REPORT_ALL_MISMATCHES=1 collects them and fails at the end.
			if os.Getenv("TOOLS_REPORT_ALL_MISMATCHES") != "" {
				mismatched = append(mismatched, fmt.Sprintf(
					"%s mismatch at function offset 0x%x (file offset 0x%x)",
					reconstruction.code.name, offset, reconstruction.code.start+offset))
				continue
			}
			return fmt.Errorf("%s mismatch at function offset 0x%x (file offset 0x%x)", reconstruction.code.name, offset, reconstruction.code.start+offset)
		}
		if err := replaceRange(got, reconstruction.code.start, reconstruction.code.end, compiled); err != nil {
			return err
		}
		countMatched(reconstruction.code.start, reconstruction.code.end)
		fmt.Printf("matching C: %s (%d bytes)\n", reconstruction.code.name, len(compiled))
		declared := map[string]bool{".text": true}
		for _, extra := range reconstruction.ranges {
			declared[extra.section] = true
			compiled, ok := compiledSections[extra.section]
			if !ok {
				return fmt.Errorf("%s did not emit declared section %s", reconstruction.code.name, extra.section)
			}
			expected := want[extra.start:extra.end]
			if offset, differs := mismatch(expected, compiled); differs {
				return fmt.Errorf("%s %s mismatch at section offset 0x%x (file offset 0x%x)", reconstruction.code.name, extra.section, offset, extra.start+offset)
			}
			if err := replaceRange(got, extra.start, extra.end, compiled); err != nil {
				return err
			}
			countMatched(extra.start, extra.end)
			fmt.Printf("matching C data: %s %s (%d bytes)\n", reconstruction.code.name, extra.section, len(compiled))
		}
		for section := range compiledSections {
			if !declared[section] {
				return fmt.Errorf("%s emitted undeclared allocatable section %s", reconstruction.code.name, section)
			}
		}
	}
	if len(mismatched) > 0 {
		for _, line := range mismatched {
			fmt.Fprintf(os.Stderr, "MISMATCH: %s\n", line)
		}
		return fmt.Errorf("%d reconstruction(s) did not match", len(mismatched))
	}
	output := filepath.Join(buildDir, outputName)
	if err := os.WriteFile(output, got, 0o644); err != nil {
		return err
	}
	fmt.Printf("matching C total: %d bytes across %d functions\n", matchedBytes, len(reconstructions))
	relativeOutput, err := filepath.Rel(p.root, output)
	if err != nil {
		return err
	}
	fmt.Printf("byte-exact: %s (%d bytes)\n", filepath.ToSlash(relativeOutput), len(got))
	return nil
}

func xmlAttribute(value string) string {
	var escaped bytes.Buffer
	_ = xml.EscapeText(&escaped, []byte(value))
	return escaped.String()
}

func readMode2File(imagePath string, lba, size int) ([]byte, error) {
	const rawSectorSize, dataOffset, dataSize = 2352, 24, 2048
	image, err := os.Open(imagePath)
	if err != nil {
		return nil, err
	}
	defer image.Close()
	output := make([]byte, size)
	for offset := 0; offset < size; offset += dataSize {
		chunk := min(dataSize, size-offset)
		position := int64((lba+offset/dataSize)*rawSectorSize + dataOffset)
		if _, err := image.ReadAt(output[offset:offset+chunk], position); err != nil {
			return nil, err
		}
	}
	return output, nil
}

func (p project) buildDisc() error {
	if err := p.checkConfig(); err != nil {
		return err
	}
	modules, err := loadModulesConfig(filepath.Join(p.root, "config", "modules.yaml"))
	if err != nil {
		return err
	}
	built := make(map[string]string)
	for _, module := range modules.Modules {
		if len(module.Reconstructions) == 0 {
			continue
		}
		output, err := p.buildModule(module, modules)
		if err != nil {
			return err
		}
		built[module.ID] = output
	}
	buildDir := filepath.Join(p.root, "build", "disc")
	if err := os.MkdirAll(buildDir, 0o755); err != nil {
		return err
	}
	projectXML, err := os.ReadFile(p.xmlPath)
	if err != nil {
		return errors.New("run `make bootstrap` first")
	}
	filesRoot := xmlAttribute(filepath.ToSlash(p.filesRoot))
	projectText := strings.ReplaceAll(string(projectXML), `source="files/`, `source="`+filesRoot+`/`)
	for _, module := range modules.Modules {
		output, ok := built[module.ID]
		if !ok {
			continue
		}
		from := `source="` + filesRoot + `/` + module.DiscPath + `"`
		to := `source="` + xmlAttribute(filepath.ToSlash(output)) + `"`
		updated := strings.Replace(projectText, from, to, 1)
		if updated == projectText {
			return fmt.Errorf("could not redirect %s in disc project", module.DiscPath)
		}
		projectText = updated
	}
	projectText = strings.Replace(projectText, `file="files/license_data.dat"`, `file="`+filesRoot+`/license_data.dat"`, 1)
	buildXML := filepath.Join(buildDir, "disc.xml")
	if err := os.WriteFile(buildXML, []byte(projectText), 0o644); err != nil {
		return err
	}
	output := filepath.Join(buildDir, "fft-us-scus-94221.bin")
	cue := filepath.Join(buildDir, "fft-us-scus-94221.cue")
	if err := runInDir(p.root, "mkpsxiso", "-q", "-y", "-o", output, "-c", cue, buildXML); err != nil {
		return err
	}
	for _, module := range modules.Modules {
		path, ok := built[module.ID]
		if !ok {
			continue
		}
		want, err := os.ReadFile(path)
		if err != nil {
			return err
		}
		got, err := readMode2File(output, module.LBA, len(want))
		if err != nil {
			return err
		}
		if offset, differs := mismatch(want, got); differs {
			return fmt.Errorf("rebuilt disc %s mismatch at file offset 0x%x", module.DiscPath, offset)
		}
		fmt.Printf("disc module exact: %s at LBA %d (%d bytes)\n", module.DiscPath, module.LBA, len(got))
	}
	config, err := p.loadConfig()
	if err != nil {
		return err
	}
	discSHA256, err := sha256File(output)
	if err != nil {
		return err
	}
	if expected := strings.ToLower(config.Checksums.SHA256); discSHA256 != expected {
		return fmt.Errorf("rebuilt disc SHA-256 mismatch: got %s, expected %s", discSHA256, expected)
	}
	fmt.Printf("disc image exact: sha256 %s\n", discSHA256)
	fmt.Printf("built disc: build/disc/fft-us-scus-94221.cue\n")
	return nil
}

func (p project) buildSmall() error {
	return p.buildRawOverlay("event-small", "EVENT/SMALL.OUT", "small-symbols.yaml", "event", "small.out", "SMALL overlay")
}
