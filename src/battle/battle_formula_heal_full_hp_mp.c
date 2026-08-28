#include "psx/types.h"

extern void battle_apply_full_hp_mp_heal(void);
extern void battle_undead_reversal(void);

/* Formula 0x4A: heal 100% HP and 100% MP. */
void battle_formula_heal_full_hp_mp(void) {
    battle_apply_full_hp_mp_heal();
    battle_undead_reversal();
}
