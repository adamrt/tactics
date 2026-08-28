#include "psx/types.h"

enum { BATTLE_WEATHER_WORD_INDEX = 0x23 };

extern s32* g_battle_script_variables;

s32 battle_get_weather(void) {
    return g_battle_script_variables[BATTLE_WEATHER_WORD_INDEX];
}
