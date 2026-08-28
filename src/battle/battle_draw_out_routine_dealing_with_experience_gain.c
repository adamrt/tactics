#include "fft/battle.h"

extern u8 D_80065CB4[];
extern u16 D_80192DB0;
extern s8 g_current_action_attack_type;
extern s8 g_current_action_data;

void battle_draw_out_routine_dealing_with_experience_gain(battle_stats_t* attacker, battle_stats_t* target, s32 arg2) {
    u16 flags;

    if (D_80065CB4[attacker->last_skillset_id] != 7)
        return;
    if (attacker->job_id == 0x5D)
        return;
    if ((arg2 & 0xFF) == 0 || ((flags = D_80192DB0) & 8) != 0) {
        D_80192DB0 = 8;
        g_current_action_attack_type = 1;
        g_current_action_data = 1;
        return;
    }
    if (flags & 0x1000) {
        target->original_brave = target->original_brave;
    }
}
