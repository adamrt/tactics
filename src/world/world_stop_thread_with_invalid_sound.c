extern void world_set_sound_effect_to_invalid(void);
extern void world_stop_current_thread(void);

void world_stop_thread_with_invalid_sound(void) {
    world_set_sound_effect_to_invalid();
    world_stop_current_thread();
}
