#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_action_state;
extern s32 main_pass_fail_roll(s32 maximum, s32 threshold);

s32 battle_chance_to_react(const battle_stats_t* unit) {
    if (g_battle_action_state != 0) {
        return 0;
    }
    return main_pass_fail_roll(0x64, unit->brave);
}
