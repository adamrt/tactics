#include "fft/battle.h"

extern void func_8007E9A8(void);
extern void func_8007EB8C(battle_misc_data_t*);

void battle_status_bubble_prep(battle_misc_data_t* unit) {
    u8 tile_offset;

    tile_offset = unit->centre_tile_offset;
    if (tile_offset != 0x2D && tile_offset != 0x31 && tile_offset != 0x39 && tile_offset != 0x35) {
        func_8007E9A8();
    }
    if (unit->status_bubble_active != 0) {
        func_8007EB8C(unit);
    }
}
