#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_current_ability_used_item_id;
extern u8 g_item_secondary_data_z_value[];
extern battle_action_data_t* g_target_current_action;

void battle_formula_heal_mp_z_times_ten(void) {
    s32 index;
    s32 amount;
    battle_action_data_t* action;

    index = g_current_ability_used_item_id;
    action = g_target_current_action;
    amount = g_item_secondary_data_z_value[index * 3];
    action->attack_type = BATTLE_ACTION_TYPE_MP_HEALING;
    action->mp_healing = amount * 10;
}
