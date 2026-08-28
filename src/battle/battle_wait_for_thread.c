#include "psx/types.h"

extern void func_8014CA80(void);
extern u8* g_event_threads;

void battle_wait_for_thread(s32 thread_id) {
    s32 offset = thread_id << 10;
    do {
        func_8014CA80();
    } while (*(s32*)(offset + (s32)g_event_threads + 0x48) != 0);
}
