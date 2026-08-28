#include "fft/battle.h"

extern s32 func_8017F020(battle_stats_t* stats);

typedef struct FloatFlyTile {
    u8 _pad0[3];
    u8 flags;
} FloatFlyTile;

s32 battle_float_fly_slope_calculation(battle_misc_data_t* unit, FloatFlyTile* tile) {
    s32 status;

    if (unit->battle_data != 0) {
        status = func_8017F020(unit->battle_data);
    } else {
        status = 0;
    }
    if (tile->flags & 0xE0) {
        if ((status & 0x40) || (status & 0x20)) {
            return (tile->flags >> 5) * 2;
        }
        if (status & 0x10) {
            return ((tile->flags >> 5) - 1) * 2;
        }
    }
    return 0;
}
