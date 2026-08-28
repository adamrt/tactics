#include "psx/types.h"

extern s32 battle_physical_evade_calculation(void);
extern void battle_store_pa_and_weapon_power(void);
extern void battle_calculate_physical_damage(void);
extern void battle_hp_absorbtion(void);

void battle_formula_absorb_hp_pa_times_wp(void) {
    if (battle_physical_evade_calculation() == 0) {
        battle_store_pa_and_weapon_power();
        battle_calculate_physical_damage();
        battle_hp_absorbtion();
    }
}
