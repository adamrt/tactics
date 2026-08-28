#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_available_item_quantities[];
extern s32 g_battle_action_state;

s32 battle_player_item_quantity_decrement(battle_stats_t* unit, s32 item_id, s32 always_one) {
    u32 idx;
    s32 qty;

    if ((unit->initial_team_flags & BATTLE_TEAM_MASK) == BATTLE_TEAM_BLUE) {
        idx = item_id & 0xFF;
        qty = g_available_item_quantities[idx];
        if (qty == 0) {
            return -1;
        }
        if (always_one == 0) {
            return 0;
        }
        if (g_battle_action_state != 0) {
            return 0;
        }
        g_available_item_quantities[idx] = qty - 1;
    }
    return 0;
}
