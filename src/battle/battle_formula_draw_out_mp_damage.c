#include "fft/battle.h"
#include "psx/types.h"

extern u16 g_current_ability_xa;
extern u16 g_current_ability_ya;
extern battle_action_data_t* g_target_current_action;
extern void calculate_katana_break_chance(void);
extern void battle_store_ma_and_y(void);
extern void battle_apply_magical_support_status_compatibility(void);

void battle_formula_draw_out_mp_damage(void) {
    u32 damage;
    battle_action_data_t* action;

    calculate_katana_break_chance();
    battle_store_ma_and_y();
    battle_apply_magical_support_status_compatibility();
    damage = g_current_ability_xa * g_current_ability_ya;
    action = g_target_current_action;
    action->attack_type = BATTLE_ACTION_TYPE_MP_DAMAGE;
    action->mp_damage = damage;
}
