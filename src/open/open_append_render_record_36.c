#include "psx/types.h"

typedef struct open_render_record_36_t {
    u32 flags;
    u8 padding_04[4];
    u8 padding_0c[8];
    u8 padding_18[8];
    u8 r;
} open_render_record_36_t;

extern s32 g_open_next_render_record_36;
extern open_render_record_36_t g_open_render_records_36[16];

s32 open_append_render_record_36(open_render_record_36_t** list, s32* count) {
    open_render_record_36_t* records = g_open_render_records_36;
    register s32 list_count __asm__("$6") = *count;
    s32 record_index = g_open_next_render_record_36;
    register s32 record_offset __asm__("$3");
    open_render_record_36_t* record;

    list_count *= 4;
    list_count += (s32)list;
    __asm__ volatile("" : "=r"(list_count) : "0"(list_count));
    record_offset = record_index * 36;
    record = (open_render_record_36_t*)(record_offset + (s32)records);
    {
        s32 clear_mask = -0x39;
        u32 flags;

        *(open_render_record_36_t**)list_count = record;
        __asm__ volatile(
            ".set noat\n"
            "lui $1,0x8008\n"
            "addiu $1,$1,0x5d04\n"
            "addu $1,$1,$3\n"
            "lw $2,0($1)\n"
            "addiu $7,$7,0x20\n"
            "lui $1,0x8008\n"
            "addiu $1,$1,0x5d18\n"
            "addu $1,$1,$3\n"
            "sw $0,0($1)\n"
            ".set at"
            : "=r"(flags), "=r"(records)
            : "r"(record_offset), "1"(records));
        flags &= clear_mask;
        __asm__ volatile(
            ".set noat\n"
            "lui $1,0x8008\n"
            "addiu $1,$1,0x5d04\n"
            "addu $1,$1,$3\n"
            "sw $2,0($1)\n"
            ".set at"
            : "=r"(flags)
            : "0"(flags), "r"(record_offset));
    }
    __asm__ volatile("addu $3,$3,$7"
        : "=r"(record_offset)
        : "0"(record_offset), "r"(records));
    *(u8*)record_offset = 0x80;
    ((u8*)records)[g_open_next_render_record_36 * 36 + 1] = 0x80;
    ((u8*)records)[g_open_next_render_record_36 * 36 + 2] = 0x80;
    (*count)++;
    {
        s32 current_record_index = g_open_next_render_record_36;
        s32 next_record_index = current_record_index + 1;
        g_open_next_render_record_36 = next_record_index;
        return current_record_index;
    }
}
