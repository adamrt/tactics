#include "fft/data.h"

extern s32* g_world_event_words;

/* Camera yaw normalised into 0..0xfff. */
s32 world_get_event_word_0x1e_mod_0x1000(void) {
    s32 value = g_world_event_words[WORLD_EVENT_WORD_CAMERA_YAW];
    while (value < 0) {
        value += 0x1000;
    }
    return value;
}
