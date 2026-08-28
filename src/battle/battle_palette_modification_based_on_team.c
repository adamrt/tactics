#include "fft/battle.h"

extern void battle_palette_modification(
    s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g, s32 h);

void battle_palette_modification_based_on_team(battle_misc_data_t* unit, s32 arg1) {
    if (unit == 0) {
        return;
    }
    if (unit->battle_data == 0) {
        return;
    }
    switch ((unit->battle_data->team_flags & BATTLE_TEAM_MASK) >> 4) {
    case 0:
        battle_palette_modification(9, arg1, 3, unit->unit_id, 0, 0, 0, 0x18);
        break;
    case 1:
        battle_palette_modification(9, arg1, 3, unit->unit_id, 0, 0x10, 0, 0);
        break;
    case 2:
        battle_palette_modification(9, arg1, 3, unit->unit_id, 0, 0, 0x10, 0);
        break;
    default:
        battle_palette_modification(9, arg1, 3, unit->unit_id, 0, 0, 0x10, 0x10);
        break;
    }
}
