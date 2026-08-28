DOCKER ?= docker
IMAGE ?= fft-decomp-dev
BEAR ?= bear
EDITOR_CC ?= clang
PCSX_REDUX ?= /Applications/PCSX-Redux.app/Contents/MacOS/PCSX-Redux
PERMUTER_DURATION ?= 60
PERMUTER_JOBS ?= 4
JOBS ?= 8
CACHE ?= 1

.DEFAULT_GOAL := help

DOCKER_RUN = $(DOCKER) run --rm \
	--user "$(shell id -u):$(shell id -g)" \
	--env HOME=/tmp \
	--env GOCACHE=/work/build/cache/go \
	--env TOOLS_JOBS=$(JOBS) \
	--env TOOLS_CACHE=$(CACHE) \
	--env TOOLS_REPORT_ALL_MISMATCHES=$(REPORT_ALL) \
	--volume "$(CURDIR):/work" \
	--workdir /work \
	$(IMAGE)

.PHONY: help bootstrap doctor check-config build analyze test run wip shell compile-commands _docker-build _image-check

help:
	@printf '%s\n' \
		'Final Fantasy Tactics matching decompilation' \
		'' \
		'  make bootstrap               Set up Docker and extract the original BIN' \
		'  make doctor                 Check the pinned Docker toolchain' \
		'  make check-config           Validate manifests and symbols' \
		'  make analyze                Rebuild the extracted MIPS analysis inventory' \
		'  make build                   Build all modules and the disc' \
		'  make build MODULE=battle     Build one module' \
		'  make test                    Test the Go tooling' \
		'  make run                     Build and launch PCSX-Redux' \
		'  make wip ACTION=...          Work on a function WIP' \
		'  make shell                   Open a shell in the Docker image' \
		'  make compile-commands        Create editor compilation metadata' \
		'' \
		'See README.md for modules, actions, and examples.'

_docker-build:
	$(DOCKER) build --tag $(IMAGE) .

_image-check:
	@$(DOCKER) image inspect $(IMAGE) >/dev/null 2>&1 || { \
		echo "Docker image $(IMAGE) is missing; run 'make bootstrap'"; \
		exit 2; \
	}

bootstrap: _docker-build doctor check-config
	$(DOCKER_RUN) tools extract

doctor: _image-check
	$(DOCKER_RUN) tools doctor

check-config: _image-check
	$(DOCKER_RUN) tools check-config

analyze: _image-check
	$(DOCKER_RUN) tools analyze

test: _image-check
	$(DOCKER_RUN) go test ./...

build: _image-check
ifeq ($(strip $(MODULE)),)
	$(DOCKER_RUN) tools build disc
else
	$(DOCKER_RUN) tools build "$(MODULE)"
endif

run:
	$(MAKE) --no-print-directory build MODULE=
	test -x "$(PCSX_REDUX)"
	"$(PCSX_REDUX)" \
		-iso "$(CURDIR)/build/disc/fft-us-scus-94221.cue" \
		-run

wip: _image-check
	@test -n "$(ACTION)" || { echo "ACTION is required: draft, match, diff, prepare, or permute"; exit 2; }
	$(DOCKER_RUN) tools wip "$(ACTION)" \
		$(if $(filter draft,$(ACTION)),"$(MODULE)" "$(SYMBOL)" "$(ADDRESS)" "$(END)" $(if $(CONTEXT),"$(CONTEXT)"),\
		$(if $(filter match diff prepare,$(ACTION)),"$(TARGET)" "$(SOURCE)" "$(LINKER)" "$(OFFSET)" "$(BYTES)" $(if $(PROFILE),"$(PROFILE)"),\
		$(if $(filter permute,$(ACTION)),"$(WORKSPACE)" "$(PERMUTER_DURATION)" "$(PERMUTER_JOBS)")))

shell: _image-check
	$(DOCKER_RUN) /bin/bash

# Editor metadata is generated on the host so paths point into this checkout.
# Authoritative compilation and validation remain in the pinned Docker image.
compile-commands:
	@command -v "$(BEAR)" >/dev/null || { echo "Bear is required (set BEAR=/path/to/bear)"; exit 2; }
	@command -v "$(EDITOR_CC)" >/dev/null || { echo "Clang is required (set EDITOR_CC=/path/to/clang)"; exit 2; }
	$(BEAR) --output compile_commands.json -- /bin/sh -c 'set -eu; find src wip -type f -name "*.c" -print | sort | while IFS= read -r source; do "$(EDITOR_CC)" -target mipsel-none-elf -march=mips1 -mabi=32 -msoft-float -fsyntax-only -undef -nostdinc -Iinclude -Wno-everything "$$source"; done'
