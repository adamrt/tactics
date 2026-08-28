extern int calculate_magical_evade(void);
extern int battle_calculate_magic_accuracy(void);
extern void battle_calculate_mp_percent_damage(void);

void battle_formula_damage_mp_percent(void) {
    if (calculate_magical_evade() == 0) {
        if (battle_calculate_magic_accuracy() == 0) {
            battle_calculate_mp_percent_damage();
        }
    }
}
