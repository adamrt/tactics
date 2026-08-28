#include "psx/types.h"

extern void* g_current_music;
extern int g_current_music_volume;
extern void SuzukiCalcMusVolChange(void* music, s16 volume, s16 time);

int main_set_current_music_target(int volume, int time) {
    void* music = g_current_music;

    if (music != 0) {
        g_current_music_volume = volume;
        SuzukiCalcMusVolChange(music, (s16)volume, (s16)time);
        return 1;
    }
    return 0;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
