#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_battle_tile_data[];
extern s32 battle_map_location_calculation(battle_stats_t*);

s32 battle_check_if_unit_can_evade(battle_stats_t* unit) {
    s32 elevation;

    if ((unit->current_status[4] & 4) != 0) {
        return 1;
    }
    if ((unit->mount_info & 0x40) != 0) {
        return 1;
    }
    /* Tile byte 3: depth in the low bits, height/2 in the top three. */
    elevation = g_battle_tile_data[battle_map_location_calculation(unit) * 8 + 3] >> 5;
    if (elevation < 2) {
        return 0;
    }
    if ((unit->current_status[2] & 0x46) != 0) {
        return 0;
    }
    if ((unit->movement_abilities[2] & 0xC8) != 0) {
        return 0;
    }
    return ((unit->mount_info & 0x80) == 0) << 1;
}
