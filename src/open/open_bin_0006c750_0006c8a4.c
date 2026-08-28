#include "psx/types.h"

typedef struct OpenQuad {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 w;
    /* 0x06 */ s16 h;
} OpenQuad;

extern u8 g_open_quad_records[];

extern void func_8010849C(s32 w, s32 h, s32 param);

#define OPEN_STORE(addr, byte_offset, value)  \
    __asm__ volatile(".set noat\n"            \
                     "lui $1,0x8008\n"        \
                     "addiu $1,$1," addr "\n" \
                     "addu $1,$1,%0\n"        \
                     "sw %1,0($1)\n"          \
                     ".set at"                \
        :                                     \
        : "r"(byte_offset), "r"(value)        \
        : "$1", "memory")

#define OPEN_STORE_ZERO(addr, byte_offset)    \
    __asm__ volatile(".set noat\n"            \
                     "lui $1,0x8008\n"        \
                     "addiu $1,$1," addr "\n" \
                     "addu $1,$1,%0\n"        \
                     "sw $0,0($1)\n"          \
                     ".set at"                \
        :                                     \
        : "r"(byte_offset)                    \
        : "$1", "memory")

static inline s32 open_load_record_flags(s32 byte_offset) {
    s32 flags;
    s32 y;
    s32 half;
    s32 scaled;
    u8* color_base;

    __asm__ volatile(".set noat\n"
                     "lui $1,0x8008\n"
                     "addiu $1,$1,0x6098\n"
                     "addu $1,$1,%1\n"
                     "lw %0,0($1)\n"
                     ".set at"
        : "=r"(flags)
        : "r"(byte_offset)
        : "$1");
    return flags;
}

void open_bin_0006c750_0006c8a4(s32 index, OpenQuad quad, s32 depth, s32 param) {
    s32 offset = index * 56;
    u8* base;
    u8* rec;
    u8* quad_dst;
    u8* color_dst;
    s32 flags;
    s32 y;
    s32 half;
    s32 scaled;
    u8* color_base;

    flags = open_load_record_flags(offset);
    flags &= ~0x1C;
    OPEN_STORE("0x6098", offset, flags);
    base = g_open_quad_records;
    OPEN_STORE("0x60b4", offset, quad.x - 0x80);
    y = quad.y;
    __asm__ volatile("");
    rec = base + offset;
    OPEN_STORE("0x60a8", offset, depth);
    OPEN_STORE("0x60b8", offset, y - 0x78);
    *(s32*)(rec + 4) = 0x1E0;
    *(s32*)rec = 0;
    quad_dst = base + 8;
    *(OpenQuad*)(quad_dst + offset) = quad;
    half = quad.x / 4;
    __asm__ volatile("");
    scaled = (depth << 6) + 0x180;
    __asm__ volatile("" : "=r"(scaled) : "0"(scaled));
    OPEN_STORE("0x609c", offset, half + scaled);
    color_base = base + 0x10;
    y = quad.y;
    __asm__ volatile("");
    color_dst = color_base + offset;
    OPEN_STORE("0x60a0", offset, y);
    *(u8*)color_dst = 0x80;
    *(u8*)(color_dst + 1) = 0x80;
    *(u8*)(color_dst + 2) = 0x80;
    OPEN_STORE_ZERO("0x60ac", offset);
    func_8010849C(quad.w, quad.h, param);
}
