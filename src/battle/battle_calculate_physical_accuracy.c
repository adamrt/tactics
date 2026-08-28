#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void apply_physical_xa_modifiers(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern void use_hp_damage_as_action_hit_percent(void);

s32 battle_calculate_physical_accuracy(void) {
    apply_physical_xa_modifiers();
    battle_store_xa_plus_ya_status_damage();
    use_hp_damage_as_action_hit_percent();
    return g_target_current_action->hit == 0;
}
