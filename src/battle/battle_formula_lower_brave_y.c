extern int battle_magical_evade_calculation(void);
extern int battle_calculate_magic_accuracy(void);
extern void battle_y_brave(void);

void battle_formula_lower_brave_y(void) {
    if (battle_magical_evade_calculation() == 0) {
        if (battle_calculate_magic_accuracy() == 0) {
            battle_y_brave();
        }
    }
}
