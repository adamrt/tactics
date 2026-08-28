#include "fft/battle.h"
#include "psx/types.h"

extern u16 g_current_ability_id;
extern u8 g_current_ability_x;
extern battle_action_data_t* g_target_current_action;

void battle_determine_which_stat_will_be_reduced(void) {
    u16 ability;

    ability = g_current_ability_id;
    if (ability == 0x90 || ability == 0xC6) {
        g_target_current_action->pa_change = g_current_ability_x & 0x7F;
    } else if (ability == 0x91 || ability == 0xC7) {
        g_target_current_action->ma_change = g_current_ability_x & 0x7F;
    } else if (ability == 0x8F || ability == 0xC5) {
        g_target_current_action->sp_change = g_current_ability_x & 0x7F;
    } else {
        return;
    }
    g_target_current_action->attack_type |= 1;
}
