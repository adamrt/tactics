extern int g_current_scenario_music;

extern void set_no_forced_music(void);
extern void unload_scenario_music(int slot);

void main_unload_current_scenario_music(void) {
    int slot = g_current_scenario_music;

    set_no_forced_music();
    unload_scenario_music(slot);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
