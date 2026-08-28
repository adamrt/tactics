#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_available_item_quantities[];

s32 battle_auto_potion(battle_stats_t* unit) {
    if (unit->initial_team_flags & BATTLE_TEAM_MASK) {
        return 0xF0;
    }
    if (g_available_item_quantities[0xF0] != 0) {
        return 0xF0;
    }
    if (g_available_item_quantities[0xF1] != 0) {
        return 0xF1;
    }
    if (g_available_item_quantities[0xF2] != 0) {
        return 0xF2;
    }
    return -1;
}
