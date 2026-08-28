#include "psx/types.h"

extern void main_stop_weather_sfx_music(void);
extern void main_play_sound_2(s32 sound_id);

void wldcore_stop_music_and_play_sound(s32 sound_id) {
    main_stop_weather_sfx_music();
    main_play_sound_2(sound_id + 0x10000);
}
