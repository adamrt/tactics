#include "psx/types.h"

extern u8 g_ability_targets_list[16];

/* Remove target_battle_id from the pending-target ring (g_ability_targets_list), shift
   the trailing entries down, and terminate the list with 0xFF. No-op if
   the id is not present. */
void battle_sort_target_list(s32 target_battle_id) {
    s32 i;

    for (i = 0; i < 16; i++) {
        if (g_ability_targets_list[i] == (target_battle_id & 0xFF)) {
            for (; i < 15; i++) {
                g_ability_targets_list[i] = g_ability_targets_list[i + 1];
            }
            g_ability_targets_list[15] = 0xFF;
            return;
        }
    }
}
