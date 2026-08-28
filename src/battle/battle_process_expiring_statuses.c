#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t battle_stats[];
extern battle_stats_t* g_current_target;
extern battle_action_data_t* g_target_current_action;
extern void battle_set_action_target_variables(battle_stats_t* unit);
extern s32 func_80184B24(s32 arg0);

void battle_process_expiring_statuses(s32 unit_id) {
    s32 i;
    s32 byte_idx;
    s32 mask;
    battle_stats_t* target;
    battle_action_data_t* action;
    s32 n;

    battle_set_action_target_variables(&battle_stats[unit_id]);

    /* Statuses 24..38 (bytes 3 and 4): tick the CT of each inflicted,
       non-innate status and flag it for removal when it reaches zero. */
    for (i = 0; i < 15; i++) {
        byte_idx = (i / 8) + 3;
        target = g_current_target;
        mask = 0x80 >> (i & 7);
        if (target->inflicted_status[byte_idx] & mask) {
            if ((target->innate_status[byte_idx] & mask) == 0) {
                n = target->status_ct[i] - 1;
                target->status_ct[i] = n;
                if ((n & 0xFF) == 0) {
                    action = g_target_current_action;
                    action->status_removal[byte_idx] = mask | action->status_removal[byte_idx];
                }
            }
        }
    }

    if (func_80184B24(0) != 0) {
        g_target_current_action->attack_type = 8;
    }
}
