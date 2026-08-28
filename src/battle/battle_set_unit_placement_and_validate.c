#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern void func_8017F6C4(s32 idx);

void battle_set_unit_placement_and_validate(s32 unit_idx, u8* src) {
    battle_stats_t* unit = &battle_stats[unit_idx];
    u16* position = &unit->position.raw;
    u32 higher_elevation;
    u32 facing;

    higher_elevation = src[3];
    higher_elevation = (higher_elevation >> 7) << 15;
    *position = (*position & 0x7FFF) | higher_elevation;
    *(u8*)position = src[2];
    unit->x = src[1];
    facing = (src[3] & 0xF) << 8;
    *position = (*position & 0xF0FF) | facing;
    func_8017F6C4(unit_idx);
}
