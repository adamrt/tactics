#include "psx/types.h"

extern void wait_frames(s32 frames);
extern void require_stop_current_event_thread_wrapper(void);

void require_wait_16_frames_and_stop_thread(void) {
    wait_frames(0x10);
    require_stop_current_event_thread_wrapper();
}
