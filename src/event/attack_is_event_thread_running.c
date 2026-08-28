#include "psx/types.h"

extern u8* g_event_threads;

s32 attack_is_event_thread_running(s32 thread_id) {
    thread_id = (thread_id << 10) + (s32)g_event_threads;
    return *(s32*)(thread_id + 0x48);
}
