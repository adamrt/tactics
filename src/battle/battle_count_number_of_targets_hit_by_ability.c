#include "psx/types.h"

extern u8 g_ability_targets_list[16];

s32 battle_count_number_of_targets_hit_by_ability(u8* out) {
    s32 count = 0;
    s32 i = 0;
    do {
        u8 v = g_ability_targets_list[i];
        *out++ = v;
        if (v != 0xFF) {
            count++;
        }
        i++;
    } while (i < 0x10);
    return count;
}
