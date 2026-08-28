#include "fft/battle.h"
#include "psx/types.h"

extern battle_action_data_t* g_target_current_action;
extern s32 battle_magical_evade_calculation(void);
extern s32 battle_calculate_magic_accuracy_without_faith(void);
extern void battle_calculate_hp_percent_damage(void);
extern void battle_weather_elemental_effects(void);
extern void battle_apply_elemental(void);
extern s32 battle_apply_elemental_absorption_and_status_proc(void);
extern void battle_apply_status(void);

/* Formula 0x53: damage (X)% of max HP, hit (MA+X)%. */
void battle_formula_damage_x_percent_hit_ma_x_percent(void) {
    if (battle_magical_evade_calculation() != 0) {
        return;
    }
    if (battle_calculate_magic_accuracy_without_faith() != 0) {
        return;
    }
    battle_calculate_hp_percent_damage();
    battle_weather_elemental_effects();
    battle_apply_elemental();
    if (g_target_current_action->hit != 0 && battle_apply_elemental_absorption_and_status_proc() == 0) {
        battle_apply_status();
    }
}
