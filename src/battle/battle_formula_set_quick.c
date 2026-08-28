extern void battle_store_ma_and_x(void);
extern int battle_calculate_friendly_magic_accuracy(void);
extern void apply_quick_effect(void);

void battle_formula_set_quick(void) {
    battle_store_ma_and_x();
    if (battle_calculate_friendly_magic_accuracy() == 0) {
        apply_quick_effect();
    }
}
