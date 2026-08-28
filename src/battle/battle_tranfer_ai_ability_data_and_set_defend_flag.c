#include "fft/battle.h"
#include "psx/types.h"

#define SUPPORT_ABILITY_DEFEND 0x1DF

/* Distinct symbols for the AI-block fields read here: naming them through
 * g_ai_data_base makes GCC share one base register where the target keeps
 * a lui per site. */
extern u8 g_ai_movement_scenario;     /* g_ai_data_base.movement_scenario */
extern battle_stats_t* g_temp_unit_data; /* g_ai_data_base.acting_unit */
extern u32 g_ai_candidate_coords[3];  /* g_ai_data_base.candidate_coords, as words */
extern battle_ai_data_t g_ai_data_base;

/* Reset the selected action to the candidate coordinates for the current
 * movement scenario; skillset 2 marks a Defend when the unit has it. */
void battle_tranfer_ai_ability_data_and_set_defend_flag(void) {
    u8 scenario = g_ai_movement_scenario;
    battle_stats_t* unit = g_temp_unit_data;
    u32 coords;
    s32 support;

    g_ai_data_base.selected_action.target_flags_set = 0;
    coords = g_ai_candidate_coords[scenario];
    support = unit->support_ability;
    g_ai_data_base.selected_action.coords.word = coords;
    if (support == SUPPORT_ABILITY_DEFEND) {
        g_ai_data_base.selected_action.skillset = 2;
    } else {
        g_ai_data_base.selected_action.skillset = 0;
    }
}
