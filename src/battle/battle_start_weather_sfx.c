#include "psx/types.h"

extern s32 g_primary_weather_sfx_id;
extern u8 g_weather_sfx_enabled;

extern void main_play_sound_2(s32 sound_id);

void battle_start_weather_sfx(void) {
    s32 sound_id;

    sound_id = g_primary_weather_sfx_id;
    g_weather_sfx_enabled = 1;
    if (sound_id != 0) {
        main_play_sound_2(sound_id);
    }
}
