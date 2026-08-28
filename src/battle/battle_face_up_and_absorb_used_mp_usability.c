#include "fft/battle.h"
#include "psx/types.h"
s32 battle_chance_to_react(s32);
extern u8 D_801938EB;
extern s32 g_current_target;
extern battle_action_data_t* g_target_current_action;
void battle_face_up_and_absorb_used_mp_usability(s16 reaction_id) {
    u8* used_mp = &D_801938EB;
    battle_action_data_t* action;
    if (*used_mp != 0) {
        if (battle_chance_to_react(g_current_target) == 0) {
            action = g_target_current_action;
            action->reaction_id = reaction_id;
            action->last_received_attack = (s16)*used_mp;
        }
    }
}
