#include "psx/types.h"

extern int func_8005E254(void*, void*, int);
extern u8 g_current_ability_attacker_facing[];
extern u8 g_ai_current_ability_data_backup[];
extern s32 g_battle_action_state;
extern s32 g_current_ability_hamedo_flag;

void battle_transfer_considered_action_data_to_ai(void) {
    g_battle_action_state = 1;
    g_current_ability_hamedo_flag = 0;
    func_8005E254(g_current_ability_attacker_facing, g_ai_current_ability_data_backup, 0x1E);
}
