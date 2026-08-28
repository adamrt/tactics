#include "psx/types.h"

typedef struct open_render_record_56_t {
    u8 pad_04[0x10];
    u8 pad_1c[0x18];
} open_render_record_56_t;

extern s32 g_open_render_record_56_count;
extern open_render_record_56_t g_open_render_records_56[];
extern u32 g_open_render_record_flags[];
extern u32 g_open_render_record_field_18[];
extern u32 g_open_render_record_field_14[];

s32 open_append_render_record_56(open_render_record_56_t** records, s32* count) {
    s32 index;
    register s32 list_index __asm__("$6");
    open_render_record_56_t* base = g_open_render_records_56;
    register s32 color __asm__("$4");
    s32 byte_offset;

    /* Preserve the retail load order before either index is consumed. */
    __asm__ volatile(
        ".set noreorder\n"
        "lui %0,%%hi(g_open_render_records_56)\n"
        "addiu %0,%0,%%lo(g_open_render_records_56)\n"
        "lw %1,0(%3)\n"
        "lui %2,%%hi(g_open_render_record_56_count)\n"
        "lw %2,%%lo(g_open_render_record_56_count)(%2)\n"
        "sll %1,%1,2\n"
        "addu %1,%1,%4\n"
        ".set reorder"
        : "=r"(base), "=r"(list_index), "=r"(index)
        : "r"(count), "r"(records)
        : "memory");
    byte_offset = (index * 7) << 3;
    /* Preserve full-address materialization and the base-to-color transition. */
    __asm__ volatile(
        ".set noreorder\n"
        ".set noat\n"
        "addu $2,%3,%0\n"
        "li $4,-0x3d\n"
        "sw $2,0(%4)\n"
        "lui $1,0x8008\n"
        "addiu $1,$1,0x6098\n"
        "addu $1,$1,%3\n"
        "lw $2,0($1)\n"
        "addiu %0,%0,0x34\n"
        "lui $1,0x8008\n"
        "addiu $1,$1,0x60b0\n"
        "addu $1,$1,%3\n"
        "sw $0,0($1)\n"
        "and $2,$2,$4\n"
        "lui $1,0x8008\n"
        "addiu $1,$1,0x6098\n"
        "addu $1,$1,%3\n"
        "sw $2,0($1)\n"
        "addu %3,%3,%0\n"
        "li %1,0x80\n"
        "sb %1,0(%3)\n"
        ".set at\n"
        ".set reorder"
        : "=r"(base), "=r"(color)
        : "0"(base), "r"(byte_offset), "r"(list_index)
        : "$1", "$2", "memory");
    *(u8*)((u8*)base + g_open_render_record_56_count * 56 + 1) = color;
    *(u8*)((u8*)base + g_open_render_record_56_count * 56 + 2) = color;
    {
        s32 field_offset = g_open_render_record_56_count * 56;

        /* Keep noreorder active through the compiler-emitted return. */
        __asm__ volatile(
            ".set noreorder\n"
            ".set noat\n"
            "lui $1,%%hi(g_open_render_record_field_14)\n"
            "addiu $1,$1,%%lo(g_open_render_record_field_14)\n"
            "addu $1,$1,%0\n"
            "sw $0,0($1)\n"
            ".set at"
            :
            : "r"(field_offset)
            : "$1", "memory");
    }
    (*count)++;
    return g_open_render_record_56_count++;
}
