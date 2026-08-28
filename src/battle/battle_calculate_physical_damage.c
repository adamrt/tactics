extern void apply_physical_xa_modifiers(void);
extern void calculate_critical_hit(void);
extern void battle_store_xa_times_ya_damage(void);

void battle_calculate_physical_damage(void) {
    apply_physical_xa_modifiers();
    calculate_critical_hit();
    battle_store_xa_times_ya_damage();
}
