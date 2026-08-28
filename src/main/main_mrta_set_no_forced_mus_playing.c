#include "psx/types.h"

extern void SuzukiDeallocateMUSChannels(s32 handle);

extern s32 g_current_scenario_music;
extern s32 g_current_music;
extern s32 g_forced_music;

s32 main_mrta_set_no_forced_mus_playing(void) {
    s32* music = &g_current_music;
    s32 result = 0;

    if (*music != 0) {
        SuzukiDeallocateMUSChannels(*music);
        result = 1;
        g_current_scenario_music = 0;
        g_forced_music = 0;
        *music = 0;
    }
    return result;
}
