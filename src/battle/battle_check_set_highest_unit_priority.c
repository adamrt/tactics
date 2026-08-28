#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;
extern s32 func_8019D37C(void);
extern s32 set_highest_target_priority(battle_ai_action_data_t* a, battle_ai_action_data_t* b);
extern void battle_transfer_halfword_values(void* dst, void* src, s32 bytes);

s32 battle_check_set_highest_unit_priority(void) {
    battle_ai_data_t* ai = &g_ai_data_base;
    s32 result = func_8019D37C();

    if (result == -1) {
        return -1;
    }
    if (result != 0) {
        if (set_highest_target_priority(&ai->current_action, &ai->best_action) != 0) {
            battle_transfer_halfword_values(&ai->best_action, &ai->current_action, sizeof(battle_ai_action_data_t));
        }
    }
    return 0;
}
