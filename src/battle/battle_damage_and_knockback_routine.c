#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_current_attacker;
extern battle_stats_t* g_target_unit_data;
extern u8 g_current_ability_y;
extern u16 g_current_ability_xa;
extern s32 g_battle_action_state;

extern s32 battle_random_process_gives_a_number_between_0_7fff(void);
extern s32 main_pass_fail_roll(s32 maximum, s32 threshold);
extern void func_801843EC(void);

void battle_damage_and_knockback_routine(void) {
    battle_action_data_t* action;
    s32 damage;
    s32 roll;
    s32 state;

    damage = (((battle_random_process_gives_a_number_between_0_7fff() * g_current_ability_y) / 32768) + 1) * g_current_ability_xa;
    action = g_target_current_action;
    action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
    state = g_battle_action_state;
    action->hp_damage = (s16)damage;
    if (state != 0) {
        return;
    }
    roll = (battle_random_process_gives_a_number_between_0_7fff() * g_current_attacker->brave) / 32768;
    if (main_pass_fail_roll(g_target_unit_data->brave, roll) == 0) {
        func_801843EC();
    }
}
