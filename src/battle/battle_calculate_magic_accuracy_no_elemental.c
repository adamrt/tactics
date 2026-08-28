#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void battle_store_ma_and_x(void);
extern void battle_apply_magical_support_status_compatibility(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern void apply_faith_to_action_damage(void);
extern void use_hp_damage_as_action_hit_percent(void);

s32 battle_calculate_magic_accuracy_no_elemental(void) {
    battle_store_ma_and_x();
    battle_apply_magical_support_status_compatibility();
    battle_store_xa_plus_ya_status_damage();
    apply_faith_to_action_damage();
    use_hp_damage_as_action_hit_percent();
    return g_target_current_action->hit == 0;
}
