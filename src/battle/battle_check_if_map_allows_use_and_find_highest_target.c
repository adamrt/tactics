#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;
extern s32 func_8019B4F4(battle_ai_coords_t*);
extern s32 func_8019D308(void);

s32 battle_check_if_map_allows_use_and_find_highest_target(void) {
    battle_ai_data_t* ai;

    ai = &g_ai_data_base;
    if (g_ai_data_base.decision_state != 0) {
        if (g_ai_data_base.find_highest_target_state != 0) {
            goto second;
        }
        goto first;
    }
    if (func_8019B4F4(&ai->acting_unit_coords) != 0) {
        g_ai_data_base.current_action.target_flags_set = 1;
    } else {
        goto check;
    }
first:
    if (func_8019D308() == -1) {
        ai->find_highest_target_state = 0;
        return -1;
    }
check:
    if (ai->current_action.coords.word == ai->acting_unit_coords.word) {
        return 0;
    }
    if (func_8019B4F4(&ai->current_action.coords) == 0) {
        return 0;
    }
    ai->current_action.target_flags_set = 0;
second:
    if (func_8019D308() != -1) {
        return 0;
    }
    ai->find_highest_target_state = 1;
    return -1;
}
