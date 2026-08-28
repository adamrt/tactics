#include "fft/battle.h"
#include "psx/types.h"

extern u16 g_current_ability_elemental_flags;
extern s16 g_current_ability_reaction_id;
extern battle_action_data_t* g_target_current_action;

void battle_called_by_nullify_action(void) {
    u16* pflag;
    battle_action_data_t* action;
    u16* special_effect;
    pflag = &g_current_ability_elemental_flags;
    if (*pflag != 0) {
        action = g_target_current_action;
        g_current_ability_reaction_id = 0;
        *pflag = 0;
        /* Clear the nullify bit (0x0200).  Reading the field through a
         * second pointer keeps the lhu below the two scalar global stores;
         * a direct action->special_effect load is hoisted above them
         * (MEM_IN_STRUCT_P) and the function comes out 4 bytes short. */
        special_effect = &action->special_effect;
        *special_effect &= 0xFDFF;
    }
}
