#include "psx/types.h"

extern void world_wait(s32 frames);

/* Idle thread body: wait one frame, forever. */
void world_idle_thread_wait_forever_b(void) {
    for (;;) {
        world_wait(1);
    }
}
