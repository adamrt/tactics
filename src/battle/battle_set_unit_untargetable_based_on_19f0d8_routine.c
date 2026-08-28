#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;
extern s32 battle_see_if_ability_should_be_used_based_on_ct(s32 unit_id);

s32 battle_set_unit_untargetable_based_on_19f0d8_routine(void) {
    s32 result;
    s32 i;
    battle_ai_data_t* ai;
    u8* walk;

    result = 0;
    ai = &g_ai_data_base;
    i = 0;
    /* The target walks a pointer that starts at the block base and steps by
     * sizeof(battle_ai_unit_decision_t), reaching unit_decisions[i].enemy_flag as a
     * 0x1834 displacement; a pointer started at unit_decisions adds an addiu. */
    walk = (u8*)ai;
    do {
        if (ai->unit_targetable[i] != 0) {
            if ((ai->considered_ability.ai_flags.word & BATTLE_AI_ABILITY_FLAG_1_TARGET_ENEMIES) && (((battle_ai_unit_decision_t*)(walk + 0x182c))->enemy_flag != 0) && (battle_see_if_ability_should_be_used_based_on_ct(i) != 0)) {
                ai->unit_targetable[i] = 0;
            } else {
                result = 1;
            }
        }
        i += 1;
        walk += sizeof(battle_ai_unit_decision_t);
    } while (i < 0x15);
    return result;
}
