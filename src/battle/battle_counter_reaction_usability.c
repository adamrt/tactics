#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_current_ability_skillset;
extern u16 g_current_ability_id;
extern u8 g_current_ability_flags4;
extern battle_action_data_t* g_target_current_action;
extern s32 g_target_unit_data;
extern s32 battle_chance_to_react(s32 unit);

void battle_counter_reaction_usability(u16 reaction_id, u32 mask) {
    battle_action_data_t* action;

    if (g_current_ability_skillset == 0x15)
        return;
    if ((g_current_ability_flags4 & mask) == 0)
        return;
    if (battle_chance_to_react(g_target_unit_data) != 0)
        return;
    action = g_target_current_action;
    action->reaction_id = reaction_id;
    /* Zero-byte fence: GCC 2.6.3 treats the struct store above as never
     * aliasing the scalar global and hoists the load past it. */
    __asm__ volatile("");
    action->last_received_attack = g_current_ability_id;
}
