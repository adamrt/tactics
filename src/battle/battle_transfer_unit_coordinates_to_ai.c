#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];

void battle_transfer_unit_coordinates_to_ai(s32 unit_idx, battle_ai_coords_t* dst) {
    dst->bytes.x = battle_stats[unit_idx].x;
    dst->bytes.y = (u8)battle_stats[unit_idx].position.raw;
    dst->bytes.level = (u8)(battle_stats[unit_idx].position.raw >> 15);
    dst->bytes.zero = 0;
}
