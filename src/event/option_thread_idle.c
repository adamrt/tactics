extern void switch_to_next_event_thread(void);

/* Park this event thread while allowing the scheduler to continue. */
void option_thread_idle(void) {
    for (;;) {
        switch_to_next_event_thread();
    }
}
