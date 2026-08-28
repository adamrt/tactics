#include "fft/battle.h"

extern battle_misc_data_t* g_misc_unit_list_head;

void battle_snap_all_unit_facings_to_quadrants(void) {
    battle_misc_data_t* unit;
    s32 facing;
    u32 west;
    u32 north;
    u32 east;

    unit = g_misc_unit_list_head;
    if (unit != 0) {
        west = BATTLE_FACING_WEST;
        north = BATTLE_FACING_NORTH;
        east = BATTLE_FACING_EAST;
        do {
            facing = unit->facing & BATTLE_FACING_MASK;
            if (facing < 0x200) {
                goto south;
            }
            if (facing < 0x600) {
                unit->facing = west;
                goto next;
            }
            if (facing < 0xa00) {
                unit->facing = north;
                goto next;
            }
            if (facing < 0xe00) {
                unit->facing = east;
                goto next;
            }
        south:
            unit->facing = BATTLE_FACING_SOUTH;
        next:
            unit = (battle_misc_data_t*)unit->previous;
        } while (unit != 0);
    }
}
