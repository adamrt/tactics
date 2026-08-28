#include "fft/battle.h"
#include "psx/types.h"

extern u16 g_current_ability_xa;
extern u16 g_current_ability_ya;
extern u8 g_current_ability_x;
extern battle_action_data_t* g_target_current_action;
extern battle_action_data_t* g_attacker_current_action;

extern void battle_store_pa_and_y(void);
extern void apply_compatibility(void);

void battle_formula_damage_pa_times_y_damage_caster_pa_times_y_over_x(void) {
    s16 damage;
    battle_action_data_t* action;

    battle_store_pa_and_y();
    apply_compatibility();
    damage = g_current_ability_xa * g_current_ability_ya;
    /* Cast-pointer stores: as struct members GCC sinks them past the
     * following scalar global loads; the target keeps source order. */
    *(s16*)&g_target_current_action->hp_damage = damage;
    damage = damage / g_current_ability_x;
    action = g_attacker_current_action;
    action->hit = 1;
    *(s16*)&action->hp_damage = damage;
    g_target_current_action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
    g_attacker_current_action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
}
