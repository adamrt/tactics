extern int g_forced_music;
extern int g_current_scenario_music;
extern void set_no_forced_music(void);
extern void unload_scenario_music(int slot);
extern int open_music_into_free_slot(int track);
extern void switch_music_track(int slot, int volume, int time);

void main_set_current_music_track(int track) {
    int slot;

    if (g_forced_music != 0) {
        slot = g_current_scenario_music;
        set_no_forced_music();
        unload_scenario_music(slot);
    }
    slot = open_music_into_free_slot(track);
    if (slot != 0) {
        switch_music_track(slot, 0x7f, 0);
    }
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
