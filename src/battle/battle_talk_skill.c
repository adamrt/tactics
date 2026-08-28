#include "fft/battle.h"
#include "fft/data.h"
#include "psx/types.h"

extern u16 g_current_ability_id;
extern u8 g_current_ability_y;
extern battle_action_data_t* g_target_current_action;

extern void battle_steal_gil(void);
extern void apply_status_to_action_full(void);

void battle_talk_skill(void) {
    switch (g_current_ability_id) {
    case ABILITY_ID_TALK_NEGOTIATE:
        battle_steal_gil();
        return;
    case ABILITY_ID_TALK_PERSUADE:
        g_target_current_action->ct_change = 0x7F;
        break;
    case ABILITY_ID_TALK_PRAISE:
        g_target_current_action->brave_change = g_current_ability_y | 0x80;
        break;
    case ABILITY_ID_TALK_THREATEN:
        g_target_current_action->brave_change = g_current_ability_y & 0x7F;
        break;
    case ABILITY_ID_TALK_PREACH:
        g_target_current_action->faith_change = g_current_ability_y | 0x80;
        break;
    case ABILITY_ID_TALK_SOLUTION:
        g_target_current_action->faith_change = g_current_ability_y & 0x7F;
        break;
    default:
        apply_status_to_action_full();
        return;
    }
    g_target_current_action->attack_type = BATTLE_ACTION_TYPE_PSEUDO_STATUS;
}
