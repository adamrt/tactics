#include "psx/types.h"

extern void battle_gravi2_damage_routine(void);

/* Formula 0x3E: damage equal to the target's max HP - 1. */
void battle_formula_damage_target_max_hp_minus_one(void) {
    battle_gravi2_damage_routine();
}
