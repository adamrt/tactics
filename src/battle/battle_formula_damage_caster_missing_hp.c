extern int battle_physical_evade_calculation(void);
extern void battle_store_ma_and_x(void);
extern int battle_calculate_physical_status_accuracy(void);
extern void battle_formula_43_damage_caster_missing_hp(void);

void battle_formula_damage_caster_missing_hp(void) {
    if (battle_physical_evade_calculation() == 0) {
        battle_store_ma_and_x();
        if (battle_calculate_physical_status_accuracy() == 0) {
            battle_formula_43_damage_caster_missing_hp();
        }
    }
}
