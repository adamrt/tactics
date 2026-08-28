void advance_event_thread(void);
void stop_current_event_thread(void);

void attack_advance_and_stop_current_thread_2(void) {
    advance_event_thread();
    stop_current_event_thread();
}

/* Keep the preprocessed source stable for the legacy compiler under QEMU. */
