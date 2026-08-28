#include "fft/data.h"

/* Ramza's sprite sets (0-3) and guest roster slots (0x10 and up) cannot be
 * dismissed. */
s32 world_dismiss_able_check(s16 formation_idx) {
    world_formation_unit_t* unit = g_world_formation_unit_pointers[formation_idx];
    s32 sprite_set = unit->sprite_set;
    s32 roster_slot = unit->roster_slot;
    if (sprite_set < 4)
        return 0;
    return roster_slot < 0x10;
}
