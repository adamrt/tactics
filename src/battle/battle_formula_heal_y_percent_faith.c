#include "psx/types.h"

extern void battle_store_ma_and_x(void);
extern void battle_apply_elemental_strengthen(void);
extern s32 battle_calculate_friendly_magic_accuracy(void);
extern s32 battle_apply_status_and_check_undead(void);
extern void battle_calculate_hp_percent_damage(void);
extern void battle_undead_reversal(void);

/* Formula 0x0D: heal (Y)% of max HP, hit F(MA+X)%. */
void battle_formula_heal_y_percent_faith(void) {
    battle_store_ma_and_x();
    battle_apply_elemental_strengthen();
    if (battle_calculate_friendly_magic_accuracy() != 0) {
        return;
    }
    if (battle_apply_status_and_check_undead() == 0) {
        return;
    }
    battle_calculate_hp_percent_damage();
    battle_undead_reversal();
}
