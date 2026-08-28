#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* g_target_unit_data;
extern void battle_force_attack_miss(void);

void battle_force_sleeping_target_miss(void) {
    if ((g_target_unit_data->current_status[4] & 0x10) != 0) {
        battle_force_attack_miss();
    }
}
