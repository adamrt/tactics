#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_check_if_unit_can_react_1(battle_stats_t* unit);
extern s32 battle_chance_to_react(const battle_stats_t* unit);
extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_current_target;
extern battle_stats_t* g_current_attacker;
extern s32 g_battle_action_state;
extern u8 g_current_ability_weapon_id;

void battle_catch(void) {
    battle_stats_t* unit;
    battle_action_data_t* action;
    /* Loaded through a pointer so GCC keeps it between the struct stores
     * (a plain scalar load is assumed not to alias them and floats). */
    u8* weapon_id_ptr = &g_current_ability_weapon_id;
    s32 weapon_id;
    s32 chance;

    if (battle_check_if_unit_can_react_1(g_current_target) != 0)
        return;
    if (g_current_attacker->job_id == 0x5D)
        return;
    unit = g_current_target;
    if ((unit->reaction_abilities[3] & 8) == 0)
        return;
    chance = 0x64 - unit->brave;
    /* The target stores the accuracy as a halfword (0x2a..0x2b). */
    g_target_current_action->attack_accuracy = (s16)chance;
    if (chance != 0) {
        if (battle_chance_to_react(unit) != 0)
            return;
        if (g_battle_action_state != 0)
            return;
    }
    g_target_current_action->hit = 0;
    action = g_target_current_action;
    action->reaction_id = 0x1C2;
    weapon_id = *weapon_id_ptr;
    action->miss_type = 0xD;
    action->last_received_attack = (s16)weapon_id;
}
