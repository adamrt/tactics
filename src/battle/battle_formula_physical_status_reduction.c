extern int calculate_physical_evade(void);
extern void battle_store_pa_and_y(void);
extern int battle_calculate_physical_accuracy(void);
extern void apply_status_reduction(void);

void battle_formula_physical_status_reduction(void) {
    if (calculate_physical_evade() == 0) {
        battle_store_pa_and_y();
        if (battle_calculate_physical_accuracy() == 0) {
            apply_status_reduction();
        }
    }
}
