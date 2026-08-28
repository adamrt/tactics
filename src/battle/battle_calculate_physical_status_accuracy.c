#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void battle_apply_attack_up_and_martial_arts(void);
extern void battle_apply_physical_status_support_compatibility(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern void use_hp_damage_as_action_hit_percent(void);

s32 battle_calculate_physical_status_accuracy(void) {
    battle_apply_attack_up_and_martial_arts();
    battle_apply_physical_status_support_compatibility();
    battle_store_xa_plus_ya_status_damage();
    use_hp_damage_as_action_hit_percent();
    return g_target_current_action->hit == 0;
}
