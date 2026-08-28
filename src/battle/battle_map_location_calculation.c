#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_map_max_x;

s32 battle_map_location_calculation(battle_stats_t* unit) {
    u8 y = unit->position.bits.y;
    u16 y_elev = unit->position.raw;
    u8 x = unit->x;
    return ((y_elev >> 15) << 8) + (y * g_map_max_x) + x;
}
