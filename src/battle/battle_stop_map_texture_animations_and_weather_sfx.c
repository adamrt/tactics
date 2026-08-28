#include "psx/types.h"

enum {
    MAP_TEXTURE_ANIMATION_COUNT = 32,
};

extern s32 g_map_texture_animation_handles[];
extern u8 g_weather_sfx_enabled;

extern void battle_stop_weather_sfx(void);
extern s32 battle_stop_map_texture_animation(s32 handle);

s32 battle_stop_map_texture_animations_and_weather_sfx(void) {
    s32 index;
    s32* handle;

    battle_stop_weather_sfx();

    index = 0;
    handle = g_map_texture_animation_handles;
    do {
        if (*handle != 0) {
            battle_stop_map_texture_animation(*handle);
            *handle = 0;
        }
        index++;
        handle++;
    } while (index < MAP_TEXTURE_ANIMATION_COUNT);

    g_weather_sfx_enabled = 0;
    return 0;
}
