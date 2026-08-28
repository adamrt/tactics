#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_apply_status_and_check_undead(void);
extern s32 battle_random_process_gives_a_number_between_0_7fff(void);
extern void battle_undead_reversal(void);
extern battle_stats_t* g_current_target;
extern battle_action_data_t* g_target_current_action;
extern u8 g_current_ability_used_item_id;
extern u8 g_item_secondary_data_z_value[];

void battle_formula_heal_random_one_to_z_add_status(void) {
    battle_stats_t* unit;

    if (battle_apply_status_and_check_undead() == 0)
        return;
    unit = g_current_target;
    if ((unit->current_status[0] & 0x10) != 0) {
        g_target_current_action->hp_damage = unit->hp;
    } else {
        g_target_current_action->hp_damage = (s32)(battle_random_process_gives_a_number_between_0_7fff() * g_item_secondary_data_z_value[g_current_ability_used_item_id * 3]) / 32768 + 1;
    }
    battle_undead_reversal();
}
