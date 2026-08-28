#include "fft/battle.h"
#include "fft/data.h"
#include "psx/types.h"

extern u16 g_current_ability_id;
extern u16 g_current_ability_xa;
extern u16 g_current_ability_ya;
extern battle_action_data_t* g_target_current_action;

extern void apply_status_to_action_full(void);

void battle_song_abilities(void) {
    switch (g_current_ability_id) {
    case ABILITY_ID_SONG_ANGEL_SONG:
        g_target_current_action->mp_healing = g_current_ability_xa + g_current_ability_ya;
        g_target_current_action->attack_type = BATTLE_ACTION_TYPE_MP_HEALING;
        return;
    case ABILITY_ID_SONG_LIFE_SONG:
        g_target_current_action->hp_healing = g_current_ability_xa + g_current_ability_ya;
        g_target_current_action->attack_type = BATTLE_ACTION_TYPE_HP_HEALING;
        return;
    case ABILITY_ID_SONG_CHEER_SONG:
        g_target_current_action->sp_change = 0x81;
        break;
    case ABILITY_ID_SONG_BATTLE_SONG:
        g_target_current_action->pa_change = 0x81;
        break;
    case ABILITY_ID_SONG_MAGIC_SONG:
        g_target_current_action->ma_change = 0x81;
        break;
    case ABILITY_ID_SONG_NAMELESS_SONG:
        apply_status_to_action_full();
        return;
    case ABILITY_ID_SONG_LAST_SONG:
        g_target_current_action->ct_change = 0xFF;
        break;
    }
    g_target_current_action->attack_type = BATTLE_ACTION_TYPE_PSEUDO_STATUS;
}
