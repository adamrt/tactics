#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void battle_dragon_check(void);
extern void func_80186DBC(void);
extern void battle_apply_status(void);

void battle_formula_dragon_heal_y_percent_add_status(void) {
    battle_dragon_check();
    if (g_target_current_action->hit != 0) {
        func_80186DBC();
        battle_apply_status();
    }
}
