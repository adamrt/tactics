extern void switch_to_next_event_thread(void);

void attack_yield_current_thread_forever(void) {
    while (1) {
        switch_to_next_event_thread();
    }
}
