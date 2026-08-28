#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_chance_to_react(s32);
extern battle_action_data_t* g_target_current_action;
extern s32 g_current_target;

void battle_pa_save_ma_save_speed_save_regenerator_auto_potion_gilgame_h(s16 reaction_id) {
    battle_action_data_t* action;

    if ((g_target_current_action->attack_type & BATTLE_ACTION_TYPE_HP_DAMAGE) && battle_chance_to_react(g_current_target) == 0) {
        action = g_target_current_action;
        action->reaction_id = reaction_id;
        action->last_received_attack = action->hp_damage;
    }
}
