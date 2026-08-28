extern void set_no_forced_music(void);
extern void unload_scenario_music(int slot);
extern int main_set_play_tune_volume(int volume);

void main_unload_scenario_music_and_tunes(void) {
    set_no_forced_music();
    unload_scenario_music(1);
    unload_scenario_music(2);
    main_set_play_tune_volume(0);
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
