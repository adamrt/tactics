#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;
extern battle_stats_t battle_stats[];

/* Index of the first present unit standing on the current action's target
 * panel, or 0x15 if none. */
s32 battle_see_if_any_units_are_on_target_panel(void) {
    battle_ai_data_t* ai = &g_ai_data_base;
    s32 i;
    battle_stats_t* unit;

    for (i = 0; i < 0x15; i++) {
        unit = &battle_stats[i];
        if (unit->entd_slot != 0xFF
            && unit->x == ai->current_action.target_x
            && unit->position.bits.y == ai->current_action.target_y
            && (unit->position.raw >> 15) == ai->current_action.target_level) {
            break;
        }
    }
    return i;
}
