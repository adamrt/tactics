#include "psx/types.h"

extern void* g_current_music;
extern void SuzukiFunc13014(void* music, s16 value, s16 time);

int main_set_current_music_pitch_shift_timed(int value, int time) {
    void* music = g_current_music;

    if (music != 0) {
        SuzukiFunc13014(music, (s16)value, (s16)time);
        return 1;
    }
    return 0;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
