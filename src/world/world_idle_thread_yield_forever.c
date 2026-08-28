extern void world_switch_to_next_thread(void);

/* Idle thread body: yield to the next WORLD thread, forever. */
void world_idle_thread_yield_forever(void) {
    for (;;) {
        world_switch_to_next_thread();
    }
}
