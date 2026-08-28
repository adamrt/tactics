#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_unit_decision_t* g_ai_acting_unit_decision_ptr;
extern battle_ai_data_t g_ai_data_base;
extern u8 g_ai_acting_unit_move;

u8 battle_get_longest_range_ability_or_move(void) {
    battle_ai_unit_decision_t* acting = g_ai_acting_unit_decision_ptr;
    battle_ai_data_t* ai = &g_ai_data_base;
    /* flags 0x40: focus on target (wiki page 00009373). */
    if (acting->flags & 0x40) {
        if (ai->unit_decisions[acting->main_target_id].enemy_flag != 0) {
            return acting->lowest_range;
        }
        return acting->highest_range;
    }
    return g_ai_acting_unit_move;
}
