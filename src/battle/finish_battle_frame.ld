OUTPUT_ARCH(mips)
SECTIONS { .text 0x800787dc : SUBALIGN(4) { *(.text) } /DISCARD/ : { *(.reginfo) *(.pdr) *(.comment) *(.gnu.attributes) } }
