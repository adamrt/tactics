FROM golang:1.27.0-bookworm

ARG DEBIAN_FRONTEND=noninteractive
ARG MKPSXISO_VERSION=2.30
ARG MKPSXISO_COMMIT=54fb1644ed8741223583e2dcda358b75a205e214
ARG MIPS_GCC_VERSION=12.2.0
ARG MIPS_BINUTILS_VERSION=2.40
ARG OLD_GCC_RELEASE=0.17
ARG GCC_263_PSX_SHA256=01e6e8c4933414ea3f8d8e3bc766a1f5fafd4fc0110e0b75d1f691bd791989b1
ARG MASPSX_COMMIT=e3d591646c6471a382e2671a63462b68d09ab306
ARG M2C_COMMIT=a73bfba20a00db8a546ec84d6ebec76063ebcf60
ARG ASM_DIFFER_COMMIT=c80ea4e3d16ecc8f4c21923633f3f9b1fb534c53
ARG DECOMP_PERMUTER_COMMIT=fb516c435c6f362fbced66e171545324306b607b
ARG SPLAT_COMMIT=1d09139b886f0bece632bd8f367ccc1d3318ca2a

RUN apt-get update \
    && apt-get install --yes --no-install-recommends \
        binutils-mipsel-linux-gnu \
        build-essential \
        ca-certificates \
        cmake \
        curl \
        file \
        gcc-mipsel-linux-gnu \
        git \
        make \
        ninja-build \
        python3 \
        python3-venv \
        qemu-user \
        xxd \
    && rm -rf /var/lib/apt/lists/*

RUN test "$(mipsel-linux-gnu-gcc -dumpfullversion)" = "${MIPS_GCC_VERSION}" \
    && mipsel-linux-gnu-as --version | grep --fixed-strings " ${MIPS_BINUTILS_VERSION}"

RUN mkdir -p /opt/old-gcc/2.6.3-psx \
    && curl --fail --location --output /tmp/gcc-2.6.3-psx.tar.gz \
        "https://github.com/decompals/old-gcc/releases/download/${OLD_GCC_RELEASE}/gcc-2.6.3-psx.tar.gz" \
    && echo "${GCC_263_PSX_SHA256}  /tmp/gcc-2.6.3-psx.tar.gz" | sha256sum --check --strict \
    && tar -xzf /tmp/gcc-2.6.3-psx.tar.gz -C /opt/old-gcc/2.6.3-psx \
    && rm /tmp/gcc-2.6.3-psx.tar.gz

RUN git clone https://github.com/mkst/maspsx.git /opt/maspsx \
    && git -C /opt/maspsx checkout "${MASPSX_COMMIT}" \
    && test "$(git -C /opt/maspsx rev-parse HEAD)" = "${MASPSX_COMMIT}" \
    && rm -rf /opt/maspsx/.git

RUN python3 -m venv /opt/decomp-tools \
    && git clone https://github.com/matt-kempster/m2c.git /opt/m2c \
    && git -C /opt/m2c checkout "${M2C_COMMIT}" \
    && test "$(git -C /opt/m2c rev-parse HEAD)" = "${M2C_COMMIT}" \
    && git clone https://github.com/simonlindholm/asm-differ.git /opt/asm-differ \
    && git -C /opt/asm-differ checkout "${ASM_DIFFER_COMMIT}" \
    && test "$(git -C /opt/asm-differ rev-parse HEAD)" = "${ASM_DIFFER_COMMIT}" \
    && git clone https://github.com/simonlindholm/decomp-permuter.git /opt/decomp-permuter \
    && git -C /opt/decomp-permuter checkout "${DECOMP_PERMUTER_COMMIT}" \
    && test "$(git -C /opt/decomp-permuter rev-parse HEAD)" = "${DECOMP_PERMUTER_COMMIT}" \
    && git clone https://github.com/ethteck/splat.git /opt/splat \
    && git -C /opt/splat checkout "${SPLAT_COMMIT}" \
    && test "$(git -C /opt/splat rev-parse HEAD)" = "${SPLAT_COMMIT}" \
    && /opt/decomp-tools/bin/pip install --no-cache-dir \
        /opt/m2c \
        /opt/asm-differ \
        '/opt/splat[mips]' \
        colorama==0.4.6 \
        crunch64==0.6.2 \
        cxxfilt==0.3.0 \
        graphviz==0.20.3 \
        intervaltree==3.1.0 \
        toml==0.10.2 \
        Levenshtein==0.27.1 \
        n64img==0.3.3 \
        pygfxd==1.0.5 \
        pylibyaml==0.1.0 \
        pypng==0.20220715.0 \
        PyYAML==6.0.3 \
        rabbitizer==1.16.2 \
        rapidfuzz==3.14.6 \
        sortedcontainers==2.4.0 \
        spimdisasm==1.42.4 \
        tqdm==4.67.1 \
        watchdog==6.0.0 \
    && ln -s /opt/decomp-permuter/permuter.py /opt/decomp-tools/bin/decomp-permuter \
    && ln -s /opt/decomp-permuter/import.py /opt/decomp-tools/bin/decomp-permuter-import \
    && rm -rf /opt/m2c/.git /opt/asm-differ/.git /opt/decomp-permuter/.git /opt/splat/.git \
    && /opt/decomp-tools/bin/m2c --help >/dev/null \
    && /opt/decomp-tools/bin/python -c 'import diff' \
    && /opt/decomp-tools/bin/python /opt/decomp-permuter/permuter.py --help >/dev/null \
    && /opt/decomp-tools/bin/splat --help >/dev/null

RUN git clone \
        --branch "v${MKPSXISO_VERSION}" \
        --depth 1 \
        --recurse-submodules \
        --shallow-submodules \
        https://github.com/Lameguy64/mkpsxiso.git /opt/src/mkpsxiso \
    && test "$(git -C /opt/src/mkpsxiso rev-parse HEAD)" = "${MKPSXISO_COMMIT}" \
    && cmake --preset release -DMKPSXISO_NO_LIBFLAC=1 -S /opt/src/mkpsxiso \
    && cmake --build /opt/src/mkpsxiso/build --parallel \
    && cmake --install /opt/src/mkpsxiso/build --prefix /usr/local \
    && rm -rf /opt/src/mkpsxiso

COPY go.mod /opt/tools/go.mod
COPY go.sum /opt/tools/go.sum
RUN cd /opt/tools && go mod download
COPY cmd/tools /opt/tools/cmd/tools
RUN cd /opt/tools && go test ./... && go build -o /usr/local/bin/tools ./cmd/tools

ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8
ENV PATH="/opt/decomp-tools/bin:${PATH}"

WORKDIR /work
CMD ["/bin/bash"]
