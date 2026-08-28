extern int calculate_magical_evade(void);
extern void battle_store_ma_and_y(void);
extern void battle_apply_elemental_strengthen(void);
extern void battle_apply_magical_support_status_compatibility(void);
extern int battle_calculate_elemental_xa_times_ya(void);
extern void apply_faith_to_action_damage(void);
extern int battle_apply_elemental_absorption_and_status_proc(void);
extern void apply_status_to_action(void);

void battle_formula_magical_damage(void) {
    if (calculate_magical_evade() == 0) {
        battle_store_ma_and_y();
        battle_apply_elemental_strengthen();
        battle_apply_magical_support_status_compatibility();
        if (battle_calculate_elemental_xa_times_ya() == 0) {
            apply_faith_to_action_damage();
            if (battle_apply_elemental_absorption_and_status_proc() == 0) {
                apply_status_to_action();
            }
        }
    }
}
