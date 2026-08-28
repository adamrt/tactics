#include "psx/types.h"

extern void battle_wait_for_thread(s32 thread_id);

void battle_wait_for_threads_10_to_13(void) {
    battle_wait_for_thread(0xD);
    battle_wait_for_thread(0xC);
    battle_wait_for_thread(0xB);
    battle_wait_for_thread(0xA);
}
