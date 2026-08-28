extern int battle_physical_evade_calculation(void);
extern void battle_store_ma_and_x(void);
extern int battle_calculate_physical_status_accuracy(void);
extern void func_80187F24(void);

void battle_formula_hit_ma_x_percent(void) {
    if (battle_physical_evade_calculation() == 0) {
        battle_store_ma_and_x();
        if (battle_calculate_physical_status_accuracy() == 0) {
            func_80187F24();
        }
    }
}
