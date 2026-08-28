#include "psx/types.h"

extern void world_wait_for_thread(s32 thread_id);

void world_wait_for_threads_10_to_13(void) {
    world_wait_for_thread(0xD);
    world_wait_for_thread(0xC);
    world_wait_for_thread(0xB);
    world_wait_for_thread(0xA);
}
