extern void world_switch_to_next_thread(void);

/* Yield to the next WORLD thread, forever. */
void world_yield_forever(void) {
    for (;;) {
        world_switch_to_next_thread();
    }
}
