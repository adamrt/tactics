#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_target_unit_data;
extern void battle_apply_status(void);
extern void battle_nullify_action(void);

s32 battle_apply_status_and_check_undead(void) {
    battle_apply_status();
    if (g_target_current_action->attack_type & 8) {
        return 1;
    }
    if (g_target_unit_data->current_status[0] & 0x10) {
        return 1;
    }
    battle_nullify_action();
    g_target_current_action->miss_type = 7;
    return 0;
}
