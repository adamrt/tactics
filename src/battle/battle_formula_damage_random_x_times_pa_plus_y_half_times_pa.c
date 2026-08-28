#include "fft/battle.h"
#include "psx/types.h"

extern s32 calculate_physical_evade(void);
extern void battle_store_pa_and_pa_plus_y_divided_by_two(void);
extern void battle_apply_attack_up_and_martial_arts(void);
extern void battle_apply_physical_status_support_compatibility(void);
extern void battle_critical_hit_calculation(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern s32 battle_random_process_gives_a_number_between_0_7fff(void);
extern u8 g_current_ability_x;
extern u8 D_801938EA;
extern battle_action_data_t* g_target_current_action;

void battle_formula_damage_random_x_times_pa_plus_y_half_times_pa(void) {
    battle_action_data_t* action;
    u8* mult;
    s32 rnd;

    if (calculate_physical_evade() != 0)
        return;
    battle_store_pa_and_pa_plus_y_divided_by_two();
    battle_apply_attack_up_and_martial_arts();
    battle_apply_physical_status_support_compatibility();
    battle_critical_hit_calculation();
    battle_store_xa_plus_ya_status_damage();
    rnd = battle_random_process_gives_a_number_between_0_7fff();
    mult = &D_801938EA;
    *mult = (s32)(rnd * g_current_ability_x) / 32768 + 1;
    action = g_target_current_action;
    /* The target loads hp_damage signed (lh) here; keep the cast and the
       multiplier deref separated so `* *` never reads as a comment. */
    *(s16*)&action->hp_damage = *(s16*)&action->hp_damage * (*mult);
    action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
}
