#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;

extern s32 rand(void);
extern void battle_transfer_halfword_values(battle_ai_action_data_t*, battle_ai_action_data_t*, s32);

s32 battle_randomly_transfer_data(void) {
    battle_ai_data_t* ai = &g_ai_data_base;
    s32 i;
    s32 any;
    s32 chance;

    any = 0;
    for (i = 0; i < 8; i++) {
        chance = ai->ranked_actions[i].base_hit_percent;
        if (chance != 0) {
            any = 1;
        }
        if ((rand() % 100) < chance) {
            battle_transfer_halfword_values(&ai->selected_action, &ai->ranked_actions[i], sizeof(battle_ai_action_data_t));
            return 1;
        }
    }
    if (any == 0) {
        return 0;
    }
    battle_transfer_halfword_values(&ai->selected_action, &ai->ranked_actions[0], sizeof(battle_ai_action_data_t));
    return 1;
}
