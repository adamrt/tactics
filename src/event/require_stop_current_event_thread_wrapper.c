extern void stop_current_event_thread(void);

void require_stop_current_event_thread_wrapper(void) {
    stop_current_event_thread();
}
