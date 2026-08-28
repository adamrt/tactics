extern int calculate_physical_evade(void);
extern void battle_store_speed_and_x(void);
extern int battle_calculate_physical_status_accuracy(void);
extern void apply_steal_gil(void);

void battle_formula_steal_gil(void) {
    if (calculate_physical_evade() == 0) {
        battle_store_speed_and_x();
        if (battle_calculate_physical_status_accuracy() == 0) {
            apply_steal_gil();
        }
    }
}
