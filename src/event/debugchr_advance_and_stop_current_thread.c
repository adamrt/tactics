extern void advance_event_thread(void);
extern void stop_current_event_thread(void);

void debugchr_advance_and_stop_current_thread(void) {
    advance_event_thread();
    stop_current_event_thread();
}
