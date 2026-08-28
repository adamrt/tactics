#include "psx/types.h"

extern u8 g_ability_targets_list[16];

void battle_store_ability_data(u8* src) {
    s32 i = 0;
    do {
        g_ability_targets_list[i] = *src;
        i++;
        src++;
    } while (i < 16);
}
