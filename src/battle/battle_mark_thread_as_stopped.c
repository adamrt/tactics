#include "psx/types.h"

extern u8* g_event_threads;

void battle_mark_thread_as_stopped(s32 thread_id) {
    thread_id <<= 10;
    *(s32*)((u8*)thread_id + (s32)g_event_threads + 0x48) = 0;
}
