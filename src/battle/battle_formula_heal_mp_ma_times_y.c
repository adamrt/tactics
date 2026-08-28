extern void battle_store_ma_and_y(void);
extern void battle_calculate_magical_xa_times_ya(void);
extern void battle_convert_hp_damage_to_mp_recovery(void);

/* Formula 0x54: heal (MA * Y) MP. */
void battle_formula_heal_mp_ma_times_y(void) {
    battle_store_ma_and_y();
    battle_calculate_magical_xa_times_ya();
    battle_convert_hp_damage_to_mp_recovery();
}
