extern void battle_setup_weapon_formula_xa_ya(void);
extern void battle_apply_physical_status_support_compatibility(void);
extern void battle_store_xa_times_ya_damage(void);

/* Formula 0x64: damage (PA * WP); spear (PA * 3/2 * WP); weaponless (PA * Brave/100 * WP). */
void battle_formula_damage_pa_times_wp(void) {
    battle_setup_weapon_formula_xa_ya();
    battle_apply_physical_status_support_compatibility();
    battle_store_xa_times_ya_damage();
}
