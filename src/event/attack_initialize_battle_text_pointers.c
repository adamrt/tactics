#include "psx/types.h"

extern u8* g_battle_text_pointers[32];

void attack_initialize_battle_text_pointers(s32* offsets) {
    s32 i;
    u8* data;
    u8** table;

    i = 0;
    data = (u8*)offsets + 0x80;
    table = g_battle_text_pointers;
    do {
        if (i != 0) {
            *table = data + *offsets;
        }
        offsets++;
        i++;
        table++;
    } while (i < 32);
}
