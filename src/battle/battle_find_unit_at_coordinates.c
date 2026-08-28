#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];

/* Index of the first present unit standing on `coords`, or 0x15 if none. */
s32 battle_find_unit_at_coordinates(battle_ai_coords_t* coords) {
    s32 i;
    battle_stats_t* unit;

    for (i = 0; i < 0x15; i++) {
        unit = &battle_stats[i];
        if (unit->entd_slot != 0xFF
            && unit->x == coords->bytes.x
            && unit->position.bits.y == coords->bytes.y
            && (unit->position.raw >> 15) == coords->bytes.level) {
            break;
        }
    }
    return i;
}
