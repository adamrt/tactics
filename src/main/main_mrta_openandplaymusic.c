#include "psx/types.h"

extern s32 SuzukiPutPlaySMD(s32 handle);
extern s32 main_get_smd(s32 sector, s32 size);

extern s32 g_music_handles[2][7];
extern s32 g_scenario_smd_files[][2];

s32 main_mrta_openandplaymusic(s32 file_index, s32 slot) {
    s32 handle;

    if (g_music_handles[1][slot] == 0) {
        handle = main_get_smd(g_scenario_smd_files[file_index][0], g_scenario_smd_files[file_index][1]);
        g_music_handles[1][slot] = handle;
        g_music_handles[0][slot] = SuzukiPutPlaySMD(handle);
        return slot;
    }
    return 0;
}
