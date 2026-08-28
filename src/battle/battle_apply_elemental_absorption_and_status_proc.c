extern void apply_elemental_absorption(void);
extern void conditional_status_proc_roll(void);

void battle_apply_elemental_absorption_and_status_proc(void) {
    apply_elemental_absorption();
    conditional_status_proc_roll();
}
