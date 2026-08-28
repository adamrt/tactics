#include "fft/battle.h"
#include "psx/types.h"

void battle_func_8006d79c(battle_misc_data_t* unit) {
    u8 path_count;

    if (unit->animation_countdown == 0) {
        path_count = unit->movement_path_count;
        unit->centre_tile_offset = 0;
        unit->movement_path_count = 0;
        /* 0x11d has no documented name yet; it receives the cleared count. */
        ((u8*)unit)[0x11D] = path_count;
    }
}
