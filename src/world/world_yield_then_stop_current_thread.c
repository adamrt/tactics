extern void world_switch_to_next_thread(void);
extern void world_stop_current_thread(void);

void world_yield_then_stop_current_thread(void) {
    world_switch_to_next_thread();
    world_stop_current_thread();
}
