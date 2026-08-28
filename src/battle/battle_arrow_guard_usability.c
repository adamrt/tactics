#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_chance_to_react(s32);
extern u8 D_801938F3;
extern u8 g_current_ability_weapon_id;
extern u8 g_primary_item_data[];
extern battle_action_data_t* g_target_current_action;
extern s32 g_current_target;
extern s32 g_battle_action_state;

void battle_arrow_guard_usability(void) {
    battle_stats_t* target;
    battle_action_data_t* action;

    if ((D_801938F3 & 0x20) == 0) {
        return;
    }
    if ((u32)(g_primary_item_data[g_current_ability_weapon_id * 12 + 5] - 0xB) >= 2) {
        return;
    }
    target = (battle_stats_t*)g_current_target;
    action = g_target_current_action;
    /* The accuracy field is written as a halfword (sh) here. */
    action->attack_accuracy = 100 - target->brave;
    if (battle_chance_to_react(g_current_target) == 0 && g_battle_action_state == 0) {
        g_target_current_action->hit = 0;
        g_target_current_action->miss_type = 4;
        g_target_current_action->reaction_id = 0x1C4;
    }
}
