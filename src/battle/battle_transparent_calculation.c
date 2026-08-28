#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_current_attacker;
extern u8 g_current_ability_accessory_evade;
extern void main_clear_byte_data(void* dst, s32 count);

void battle_transparent_calculation(void) {
    /* Status 3 bit 0x10: Transparent. */
    if (g_current_attacker->current_status[2] & 0x10) {
        main_clear_byte_data(&g_current_ability_accessory_evade, 4);
    }
}
