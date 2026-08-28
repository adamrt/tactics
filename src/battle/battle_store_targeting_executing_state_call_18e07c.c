#include "psx/types.h"

extern void func_8018E07C(void);
extern s32 g_battle_action_state;

void battle_store_targeting_executing_state_call_18e07c(void) {
    g_battle_action_state = 2;
    func_8018E07C();
    g_battle_action_state = 0;
}
