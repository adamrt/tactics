extern void calculate_katana_break_chance(void);
extern void apply_status_to_action_full(void);

void battle_formula_draw_out_status(void) {
    calculate_katana_break_chance();
    apply_status_to_action_full();
}
