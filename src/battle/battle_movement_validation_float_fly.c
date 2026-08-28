#include "fft/battle.h"

extern u8* battle_get_tile_data_pointer(s16 x, s16 y, u8 z);
extern s32 func_8017F020(battle_stats_t* stats);

typedef struct FloatFlyTile {
    u8 _pad0[3];
    u8 flags;
} FloatFlyTile;

s32 battle_movement_validation_float_fly(battle_misc_data_t* unit) {
    FloatFlyTile* tile;
    s32 status;
    u32 flags;

    tile = (FloatFlyTile*)battle_get_tile_data_pointer(
        unit->screen_x / 28, unit->screen_y / 28, unit->map_z);
    if (unit->battle_data != 0) {
        status = func_8017F020(unit->battle_data);
        if (status & 0x20) {
            return 0;
        }
        flags = unit->status_flags_5_6;
        if (flags & 0x20) {
            return 0;
        }
        if (flags & 0xE) {
            return 1;
        }
        if (status & 0x10) {
            return 1;
        }
        if (flags & 1) {
            return 0;
        }
    }
    return tile->flags >> 5;
}
