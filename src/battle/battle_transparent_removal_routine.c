#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_target_unit_data;

extern s32 battle_crystal_dead_jump_petrify_treasure_check(battle_stats_t* unit);
extern void battle_set_action_target_variables(battle_stats_t* unit);

s32 battle_transparent_removal_routine(battle_stats_t* unit) {
    battle_stats_t* target;

    if (battle_crystal_dead_jump_petrify_treasure_check(unit) != 0) {
        return 0;
    }
    battle_set_action_target_variables(unit);
    if (unit->action_taken != 0) {
        target = g_target_unit_data;
        if ((target->inflicted_status[2] & 0x10) != 0) {
            if (target->transparent_removal_flag != 0) {
                g_target_current_action->status_removal[2] = 0x10;
                g_target_current_action->attack_type = 8;
            }
        }
    }
    return g_target_current_action->attack_type;
}
