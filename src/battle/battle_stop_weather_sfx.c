#include "psx/types.h"

extern s32 g_primary_weather_sfx_id;
extern s32 g_secondary_weather_sfx_id;
extern s32 g_tertiary_weather_sfx_id;

extern void main_stop_playing_sfx(s32 sound_id);

s32 battle_stop_weather_sfx(void) {
    s32 result;
    s32 sound_id;

    sound_id = g_primary_weather_sfx_id;
    if (sound_id != 0) {
        main_stop_playing_sfx(sound_id);
        g_primary_weather_sfx_id = 0;
    }

    sound_id = g_secondary_weather_sfx_id;
    if (sound_id != 0) {
        main_stop_playing_sfx(sound_id);
        g_secondary_weather_sfx_id = 0;
    }

    sound_id = g_tertiary_weather_sfx_id;
    if (sound_id != 0) {
        main_stop_playing_sfx(sound_id);
        g_tertiary_weather_sfx_id = 0;
    }

    /* The target returns an indeterminate saved-register value. */
    return result;
}
