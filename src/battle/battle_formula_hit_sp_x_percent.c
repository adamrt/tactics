#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void battle_store_speed_and_x(void);
extern void battle_physical_xa_modifying_statuses_support(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern void func_80187510(void);
extern void func_80187F24(void);

/* Formula 0x3F: hit (SP+X)%. */
void battle_formula_hit_sp_x_percent(void) {
    battle_store_speed_and_x();
    battle_physical_xa_modifying_statuses_support();
    battle_store_xa_plus_ya_status_damage();
    func_80187510();
    if (g_target_current_action->hit != 0) {
        func_80187F24();
    }
}
