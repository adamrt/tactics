#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void battle_dragon_check(void);
extern void battle_formula_add_brave_x_stats_y(void);

void battle_formula_dragon_brave_x_stats_y(void) {
    battle_dragon_check();
    if (g_target_current_action->hit != 0) {
        battle_formula_add_brave_x_stats_y();
    }
}
