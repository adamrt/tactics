#include "psx/types.h"

extern void battle_calculate_truth_formula_damage(void);

/* Formula 0x60: damage ((MA + Y) / 2 * MA), 6.25% status. */
void battle_formula_damage_ma_plus_y_half_times_ma_status(void) {
    battle_calculate_truth_formula_damage();
}
