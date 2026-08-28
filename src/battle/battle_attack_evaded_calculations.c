#include "fft/battle.h"
#include "psx/types.h"

extern s32 main_pass_fail_roll(s32 base, s32 threshold);
extern battle_action_data_t* g_target_current_action;
extern s32 g_battle_action_state;

s32 battle_attack_evaded_calculations(s32 numerator, s32 denominator, s8 miss_type, s8 item_lost) {
    if (main_pass_fail_roll(denominator & 0xffff, numerator & 0xffff) != 0) {
        return 0;
    }
    if (g_battle_action_state != 0) {
        return 0;
    }
    g_target_current_action->hit = 0;
    g_target_current_action->miss_type = miss_type;
    g_target_current_action->item_lost = item_lost;
    return 1;
}
