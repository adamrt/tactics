extern void battle_apply_magic_attack_up(void);
extern void apply_compatibility(void);
extern void battle_store_xa_times_ya_damage(void);

void battle_calculate_magical_xa_times_ya(void) {
    battle_apply_magic_attack_up();
    apply_compatibility();
    battle_store_xa_times_ya_damage();
}
