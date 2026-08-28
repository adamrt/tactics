#include "psx/types.h"

extern u16 g_jobstts_input_repeat_counters[8];

void jobstts_clear_input_repeat_counters(void) {
    s32 index = 7;
    u16* value = &g_jobstts_input_repeat_counters[7];

    do {
        *value = 0;
        index--;
        value--;
    } while (index >= 0);
}
