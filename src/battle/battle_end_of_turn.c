#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern u8 D_801908CD[];

s32 battle_end_of_turn(s32 unit_id) {
    battle_stats_t* unit;
    u16 ct;
    u8 status4;
    u8 movement_check;
    u8 action_check;
    u32 result;

    unit = &battle_stats[unit_id];
    if (D_801908CD[unit_id * 0x1C0] == 0xFF)
        return 1;
    if (unit->has_turn == 0)
        return 1;
    ct = unit->ct;
    status4 = unit->current_status[4];
    movement_check = unit->movement_taken | (status4 & 8);
    action_check = (status4 & 4) | unit->action_taken | (unit->current_status[0] & 1);
    if (movement_check == 0) {
        ct += 0x14;
    }
    result = ct & 0xFFFF;
    if (action_check == 0) {
        ct += 0x14;
        result = ct & 0xFFFF;
    }
    if (result >= 0x3D)
        ct = 0x3C;
    unit->ct = ct;
    unit->has_turn = 0;
    return 1;
}
