#include "fft/battle.h"

extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_current_target;

/* Battle Stats 0x91 bit 0x04 is the Maintenance support (wiki page 00000307). */
void battle_maintenance(void) {
    if (g_current_target->support_abilities[2] & 4) {
        g_target_current_action->hit = 0;
        g_target_current_action->miss_type = 7;
        g_target_current_action->attack_accuracy = 0;
    }
}
