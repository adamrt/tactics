#include "psx/types.h"

extern int g_tune_state[];
extern void SuzukiCalcMusVolChange(void* music, s16 volume, s16 time);

int main_set_play_tune_volume(int volume) {
    int tune = g_tune_state[0];

    if (tune != 0) {
        if ((tune & 0x80) != 0) {
            g_tune_state[0] = 0;
        } else {
            SuzukiCalcMusVolChange((void*)g_tune_state[3 + (tune & 0x3f)], 0,
                (s16)volume);
        }
    }
    return 1;
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
