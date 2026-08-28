#include "psx/types.h"

extern u8* g_current_target;
extern void battle_force_attack_miss(void);

void battle_dragon_check(void) {
    if ((u32)(g_current_target[0x15E] - 0xF) >= 2U) {
        battle_force_attack_miss();
    }
}
