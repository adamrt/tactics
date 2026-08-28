extern void switch_to_next_event_thread(void);
extern void stop_current_event_thread(void);

/* Give other event work one turn before terminating this thread. */
void option_yield_then_stop_thread(void) {
    switch_to_next_event_thread();
    stop_current_event_thread();
}
