extern void switch_to_next_event_thread(void);
extern void stop_current_event_thread(void);

void bunit_yield_then_stop_thread_2(void) {
    switch_to_next_event_thread();
    stop_current_event_thread();
}
