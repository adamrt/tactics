#include "psx/types.h"

extern s32 g_battle_action_state;
extern u8 g_ai_current_ability_data_backup[];
extern u8 g_current_ability_attacker_facing[];
extern void func_8005E254(u8* dst, u8* src, s32 n);

void battle_restore_considered_action_data_from_ai(void) {
    g_battle_action_state = 0;
    func_8005E254(g_ai_current_ability_data_backup, g_current_ability_attacker_facing, 0x1E);
}
