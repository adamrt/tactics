#include "fft/battle.h"
#include "fft/data.h"
#include "psx/types.h"

extern u16 g_current_ability_id;
extern u16 g_current_ability_xa;
extern u16 g_current_ability_ya;
extern battle_action_data_t* g_target_current_action;

extern void apply_status_to_action_full(void);

void battle_dance_abilities(void) {
    switch (g_current_ability_id) {
    case ABILITY_ID_DANCE_WITCH_HUNT:
        g_target_current_action->mp_damage = g_current_ability_xa + g_current_ability_ya;
        g_target_current_action->attack_type = BATTLE_ACTION_TYPE_MP_DAMAGE;
        return;
    case ABILITY_ID_DANCE_WIZNAIBUS:
        g_target_current_action->hp_damage = g_current_ability_xa + g_current_ability_ya;
        g_target_current_action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
        return;
    case ABILITY_ID_DANCE_SLOW_DANCE:
        g_target_current_action->sp_change = 1;
        break;
    case ABILITY_ID_DANCE_POLKA_POLKA:
        g_target_current_action->pa_change = 1;
        break;
    case ABILITY_ID_DANCE_DISILLUSION:
        g_target_current_action->ma_change = 1;
        break;
    case ABILITY_ID_DANCE_NAMELESS_DANCE:
        apply_status_to_action_full();
        return;
    case ABILITY_ID_DANCE_LAST_DANCE:
        g_target_current_action->ct_change = 0x7F;
        break;
    }
    g_target_current_action->attack_type = BATTLE_ACTION_TYPE_PSEUDO_STATUS;
}
