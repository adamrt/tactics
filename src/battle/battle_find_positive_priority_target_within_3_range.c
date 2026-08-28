#include "psx/types.h"

extern u8* g_ai_acting_unit_decision_ptr;
extern u8 g_ai_unit_enemy_flag;
extern void battle_get_positive_priority(s32 arg);

void battle_find_positive_priority_target_within_3_range(s32 arg0) {
    u8* t = g_ai_acting_unit_decision_ptr;
    if ((&g_ai_unit_enemy_flag)[t[5] * 0x10] != 0 && (t[6] & 1) && arg0 < 3) {
        arg0 = 3;
    }
    battle_get_positive_priority(arg0);
}
