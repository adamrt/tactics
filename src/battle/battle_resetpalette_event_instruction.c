#include "psx/types.h"

extern s16 battle_load_halfword(void);
extern s32 func_80133158(s16);
extern void battle_weather_time_tile_palette_mod_by_misc_id(s32);

void battle_resetpalette_event_instruction(void) {
    s32 v = func_80133158(battle_load_halfword());
    if (v != 0x7D0) {
        battle_weather_time_tile_palette_mod_by_misc_id(v);
    }
}
