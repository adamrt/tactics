extern void battle_apply_magic_attack_up(void);
extern void apply_magic_defense_up(void);
extern void apply_magical_status_modifiers(void);
extern void apply_compatibility(void);

void battle_apply_magical_support_status_compatibility(void) {
    battle_apply_magic_attack_up();
    apply_magic_defense_up();
    apply_magical_status_modifiers();
    apply_compatibility();
}
