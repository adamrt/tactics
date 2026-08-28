#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern s32 g_battle_action_state;
extern s32 main_pass_fail_roll(s32 numerator, s32 denominator);

void battle_conditional_status_proc_roll_inner_routine(void) {
    if (g_battle_action_state == 0 && main_pass_fail_roll(0x64, 0x13) == 0) {
        battle_action_data_t* action = g_target_current_action;
        /* Halfword RMW over special_effect/special_flags_2: sets
         * special_flags_2 bit 0x02 (nullification). */
        action->special_effect = action->special_effect | 0x200;
    }
}
