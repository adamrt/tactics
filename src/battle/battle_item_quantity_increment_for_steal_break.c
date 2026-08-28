#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_action_state;
extern u8 g_available_item_quantities[];
extern s32 get_total_equipment_quantity(s32, s32);
extern s32 battle_add_price_of_item_4_to_total_gil(battle_stats_t*, s32, s32);

s32 battle_item_quantity_increment_for_steal_break(battle_stats_t* unit, s32 arg1) {
    s32 item_id;

    if (g_battle_action_state != 0) {
        return 0;
    }
    if ((unit->initial_team_flags & BATTLE_TEAM_MASK) != 0) {
        return 0;
    }
    item_id = arg1 & 0xFF;
    if (item_id == 0) {
        return 0;
    }
    if (item_id == 0xFF) {
        return 0;
    }
    if (get_total_equipment_quantity(item_id, 1) >= 0x63) {
        return battle_add_price_of_item_4_to_total_gil(unit, 0, item_id);
    }
    g_available_item_quantities[item_id] += 1;
    return 0;
}
