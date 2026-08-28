#include "psx/types.h"

extern int g_weather_sfx_id;

extern void SuzukiSetSfxEcho(int sound_id, s16 echo);

void main_set_sfx_echo(int sound_id, int echo) {
    if (g_weather_sfx_id == sound_id && echo == 0) {
        g_weather_sfx_id = 0;
    }
    SuzukiSetSfxEcho(sound_id, echo);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
