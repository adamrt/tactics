extern void initialize_event_thread(int thread_id, void (*function)(void));
extern void wait_for_event_thread(int thread_id);
extern void stop_current_event_thread(void);
extern void require_open_jobstts_overlay(void);

void require_open_jobstts_thread(void) {
    initialize_event_thread(6, require_open_jobstts_overlay);
    wait_for_event_thread(6);
    stop_current_event_thread();
}
