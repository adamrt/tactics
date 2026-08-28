extern int battle_physical_evade_calculation(void);
extern void battle_store_pa_and_y(void);
extern void battle_apply_attack_up_and_martial_arts(void);
extern void battle_apply_physical_status_support_compatibility(void);
extern void battle_damage_and_knockback_routine(void);

void battle_formula_damage_random_y_times_pa(void) {
    if (battle_physical_evade_calculation() == 0) {
        battle_store_pa_and_y();
        battle_apply_attack_up_and_martial_arts();
        battle_apply_physical_status_support_compatibility();
        battle_damage_and_knockback_routine();
    }
}
