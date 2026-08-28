#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_temp_unit_data;

void battle_save_coordinates_to_temp_unit(u8* coord) {
    u32 higher_elevation;
    g_temp_unit_data->x = coord[0];
    g_temp_unit_data->position.bits.y = coord[2];
    higher_elevation = coord[1] << 15;
    g_temp_unit_data->position.raw = (g_temp_unit_data->position.raw & 0x7FFF) | higher_elevation;
}
