#include "fft/battle.h"
#include "psx/types.h"

extern s32 end_turn(s32 idx);
extern s32 able_to_move_act_checks(battle_stats_t* unit);
extern battle_stats_t battle_stats[];

s32 battle_set_move_act_flags(s32 idx, s32 move_flag, s32 act_flag) {
    battle_stats_t* unit;
    s32 ret;
    unit = &battle_stats[idx];
    if (unit->entd_slot == 0xFF)
        return -1;
    if (move_flag != 0) {
        unit->movement_taken = 1;
    }
    if (act_flag != 0) {
        unit->action_taken = 1;
    }
    ret = able_to_move_act_checks(unit);
    if (ret != 0) {
        ret = end_turn(idx);
    }
    return ret;
}
