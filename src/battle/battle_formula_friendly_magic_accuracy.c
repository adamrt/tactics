extern void battle_store_ma_and_x(void);
extern void battle_apply_elemental_strengthen(void);
extern int battle_calculate_friendly_magic_accuracy(void);
extern void apply_status_to_action_full(void);

void battle_formula_friendly_magic_accuracy(void) {
    battle_store_ma_and_x();
    battle_apply_elemental_strengthen();
    if (battle_calculate_friendly_magic_accuracy() == 0) {
        apply_status_to_action_full();
    }
}
