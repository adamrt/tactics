#include "fft/battle.h"
#include "psx/types.h"

extern void* g_attacker_current_action;
extern u8 g_current_action_data;
extern u8 g_current_action_attack_type;
extern u8 D_80192DC2;

void battle_remove_transparent_status_if_jump_is_used(battle_stats_t* unit) {
    u8* p = &g_current_action_data;
    g_attacker_current_action = p;
    /* Skillset 0x12 is Jump; inflicted status 3 bit 0x10 is Transparent. */
    if (unit->last_skillset_id == 0x12 && (unit->inflicted_status[2] & 0x10)) {
        *p = 1;
        g_current_action_attack_type = g_current_action_attack_type | 8;
        D_80192DC2 = D_80192DC2 | 0x10;
    }
}
