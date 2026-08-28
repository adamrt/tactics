#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void battle_store_ma_and_x(void);
extern void battle_apply_elemental_strengthen(void);
extern void battle_apply_magic_attack_up(void);
extern void func_80184964(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern void func_80187510(void);
extern void func_80187F24(void);

/* Formula 0x51: hit (MA+X)%. */
void battle_formula_51_hit_ma_x_percent(void) {
    battle_store_ma_and_x();
    battle_apply_elemental_strengthen();
    battle_apply_magic_attack_up();
    func_80184964();
    battle_store_xa_plus_ya_status_damage();
    func_80187510();
    if (g_target_current_action->hit != 0) {
        func_80187F24();
    }
}
