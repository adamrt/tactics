#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_ai_map_max_x;
extern u8 g_battle_tile_data[];

/* `coords` is an x / elevation / y byte triple, not a unit record. */
s32 battle_calculate_height_difference_between_units(u8* coords, battle_stats_t* unit) {
    u8* t;
    s32 h1;
    s32 h2;

    t = &g_battle_tile_data[((unit->position.raw >> 15) * 0x100 + unit->position.bits.y * g_ai_map_max_x + unit->x) * 8];
    h1 = t[2] * 2 + (t[3] & 0x1F);
    t = &g_battle_tile_data[((coords[1] << 8) + coords[2] * g_ai_map_max_x + coords[0]) * 8];
    h2 = t[2] * 2 + (t[3] & 0x1F);
    return (h1 - h2) / 2;
}
