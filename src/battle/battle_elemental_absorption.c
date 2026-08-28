#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;

void battle_elemental_absorption(void) {
    battle_action_data_t* action = g_target_current_action;

    if (action->miss_type != 5) {
        /* special_effect/special_flags_2 read as one halfword: 0x400 is
         * special_flags_2 bit 0x04 (absorption). */
        if (action->special_effect & 0x400) {
            u16 tmp = action->hp_damage;
            action->hp_damage = 0;
            action->attack_type = BATTLE_ACTION_TYPE_HP_HEALING;
            action->hp_healing = tmp;
        } else {
            action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
        }
    }
}
