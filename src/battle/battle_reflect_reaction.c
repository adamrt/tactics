#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_current_ability_skillset;
extern u8 D_801938F5;
extern u16 g_current_ability_id;
extern battle_action_data_t* g_target_current_action;

void battle_reflect_reaction(void) {
    battle_action_data_t* action;
    /* Loaded through a pointer so the reaction_id store stays above it. */
    u16* ability_ptr = &g_current_ability_id;
    u16 ability;
    if (g_current_ability_skillset != 0x15 && (D_801938F5 & 0x80)) {
        action = g_target_current_action;
        action->reaction_id = 0x1B8;
        ability = *ability_ptr;
        /* The target stores the accuracy as a halfword (0x2a..0x2b). */
        action->attack_accuracy = 0;
        action->hit = 0;
        action->last_received_attack = ability;
        g_target_current_action->miss_type = 9;
    }
}
