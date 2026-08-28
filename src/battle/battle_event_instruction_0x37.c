#include "psx/types.h"

extern s16 battle_load_halfword(u8* ptr);

typedef struct {
    u8 unk_00[8];
    s32 unk_08;
    u8 unk_0c[0x10];
    s32 unk_1c;
    u8 unk_20[0xf8];
} MenuBufferRecord;

extern MenuBufferRecord g_battle_menu_buffer_records[];

void battle_event_instruction_0x37(u8* ptr) {
    s32 i;
    s32 idx;
    s16 val;
    MenuBufferRecord* rec;

    val = battle_load_halfword(ptr);
    for (i = 0; i < 6; i++) {
        if (g_battle_menu_buffer_records[idx].unk_08 == val) {
            rec = &g_battle_menu_buffer_records[idx];
            rec->unk_1c = g_battle_menu_buffer_records[idx].unk_1c + 1;
            g_battle_menu_buffer_records[idx].unk_1c = g_battle_menu_buffer_records[idx].unk_1c & 1;
        }
    }
}
