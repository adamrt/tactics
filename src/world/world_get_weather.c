#include "psx/types.h"

enum { WORLD_WEATHER_WORD_INDEX = 0x23 };

extern s32* g_world_event_words;

s32 world_get_weather(void) {
    return g_world_event_words[WORLD_WEATHER_WORD_INDEX];
}
