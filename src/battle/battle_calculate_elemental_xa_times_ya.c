#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern void battle_store_xa_times_ya_damage(void);
extern void apply_weather_elemental_effects(void);
extern void apply_ability_elemental_effects(void);

s32 battle_calculate_elemental_xa_times_ya(void) {
    battle_store_xa_times_ya_damage();
    apply_weather_elemental_effects();
    apply_ability_elemental_effects();
    return g_target_current_action->hit == 0;
}
