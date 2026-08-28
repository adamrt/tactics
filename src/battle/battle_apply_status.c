#include "fft/battle.h"
#include "psx/types.h"

extern void func_80187F24(void);
extern battle_action_data_t* g_target_current_action;

void battle_apply_status(void) {
    u8 hit, miss_type;
    u16 accuracy;

    miss_type = g_target_current_action->miss_type;
    /* The accuracy field is read and written as a halfword (lhu/sh). */
    accuracy = g_target_current_action->attack_accuracy;
    hit = g_target_current_action->hit;
    func_80187F24();
    g_target_current_action->hit = hit;
    g_target_current_action->attack_accuracy = accuracy;
    g_target_current_action->miss_type = miss_type;
}
