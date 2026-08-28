#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_target_unit_data;
extern void battle_store_speed_and_x(void);
extern void battle_physical_xa_modifying_statuses_support(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern void func_80187510(void);
extern void battle_force_attack_miss(void);
extern void func_80187f24(void);

/* Formula 0x40: undead targets only, hit (SP+X)%. */
void battle_formula_undead_hit_sp_x_percent(void) {
    battle_store_speed_and_x();
    battle_physical_xa_modifying_statuses_support();
    battle_store_xa_plus_ya_status_damage();
    func_80187510();
    if (g_target_current_action->hit != 0) {
        if ((g_target_unit_data->current_status[0] & 0x10) == 0) {
            battle_force_attack_miss();
        } else {
            func_80187f24();
        }
    }
}
