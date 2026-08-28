#include "psx/types.h"

extern void SuzukiUnloadMUS(s32 handle);
extern s32 main_mrta_smd_realloc(void* ptr);

extern s32 g_music_handles[2][7];

s32 main_mrta_unload_scenario_mus(s32 index) {
    if (g_music_handles[1][index] != 0) {
        SuzukiUnloadMUS(g_music_handles[0][index]);
        g_music_handles[0][index] = 0;
        main_mrta_smd_realloc((void*)g_music_handles[1][index]);
        g_music_handles[1][index] = 0;
        return 1;
    }
    return 0;
}
