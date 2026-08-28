#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_current_attacker;
extern u8 g_current_ability_base_hit;
extern void battle_transparent_calculation(void);

void battle_dark_confuse_caclulation(void) {
    if (g_current_attacker->current_status[1] & 0x30) {
        u8* p = &g_current_ability_base_hit;
        *p = *p >> 1;
    }
    battle_transparent_calculation();
}
