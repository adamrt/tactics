#include "fft/battle.h"
#include "psx/types.h"

extern u16 g_current_ability_reaction_id;
extern u16 g_current_ability_elemental_flags;

s32 battle_reaction_check(battle_stats_t* unit) {
    s32 v;
    if (g_current_ability_reaction_id != 0) {
        if (g_current_ability_elemental_flags == 0)
            return 1;
    }
    /* The target loads the reaction id signed (lh). */
    v = *(s16*)&unit->action.reaction_id;
    if (v != 0)
        v = 2;
    return v;
}
