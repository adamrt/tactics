extern int battle_magical_evade_calculation(void);
extern int battle_calculate_magic_accuracy_without_faith(void);
extern void battle_y_brave(void);

void battle_formula_lower_brave_y_without_faith(void) {
    if (battle_magical_evade_calculation() == 0) {
        if (battle_calculate_magic_accuracy_without_faith() == 0) {
            battle_y_brave();
        }
    }
}
