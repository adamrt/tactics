#include "psx/types.h"

extern u8 g_current_ability_knockback_flags;
extern u16* g_target_current_action;

void battle_remove_knockback_flag(void) {
    u8* flag = &g_current_ability_knockback_flags;
    u16* p;
    if ((*flag & 0x80) != 0) {
        p = g_target_current_action;
        *flag = 0;
        p[8] = (u16)(p[8] & 0xBFFF);
    }
}
