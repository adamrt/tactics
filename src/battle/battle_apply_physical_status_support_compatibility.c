extern void battle_apply_attacker_berserk_frog(void);
extern void apply_defense_up(void);
extern void apply_physical_target_status_modifiers(void);
extern void apply_compatibility(void);

void battle_apply_physical_status_support_compatibility(void) {
    battle_apply_attacker_berserk_frog();
    apply_defense_up();
    apply_physical_target_status_modifiers();
    apply_compatibility();
}
