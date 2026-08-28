#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_chance_to_react(s32);
extern battle_action_data_t* g_target_current_action;
extern s32 g_current_target;

void battle_damage_split_usability(void) {
    u16 hp;
    battle_action_data_t* action;

    hp = g_target_current_action->hp_damage;
    if (hp != 0 && battle_chance_to_react(g_current_target) == 0) {
        hp++;
        hp = ((u16)hp) >> 1;
        action = g_target_current_action;
        action->last_received_attack = hp;
        action->reaction_id = 0x1BE;
    }
}
