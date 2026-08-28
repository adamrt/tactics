#include "psx/types.h"

extern s32 battle_physical_evade_calculation(void);
extern void battle_store_ma_and_x(void);
extern s32 battle_calculate_physical_status_accuracy(void);
extern void battle_calculate_hp_percent_damage(void);
extern void battle_hp_absorbtion(void);

/* Formula 0x4D: absorb (Y)% of max HP, hit (MA+X)%. */
void battle_formula_absorb_hp_y_percent_hit_ma_x_percent(void) {
    if (battle_physical_evade_calculation() != 0) {
        return;
    }
    battle_store_ma_and_x();
    if (battle_calculate_physical_status_accuracy() != 0) {
        return;
    }
    battle_calculate_hp_percent_damage();
    battle_hp_absorbtion();
}
