#include "psx/types.h"

extern void* battle_return_global_pointer(void);
extern u8* g_event_threads;

void battle_thread_initialize(s32 thread_id, s32 arg1) {
    u8* t;
    void* gp;

    gp = battle_return_global_pointer();
    t = g_event_threads + (thread_id << 10);
    *(void**)(t + 0x38) = gp;
    *(u8**)(t + 0x3C) = t + 0x3F0;
    *(u8**)(t + 0x40) = t + 0x3F0;
    *(s32*)(t + 0x44) = arg1;
    *(s32*)(t + 0x48) = 1;
    *(s32*)(t + 0x4C) = 0;
    *(s32*)(t + 0x0C) = 0;
    *(s32*)(t + 0x50) = 0;
    *(s32*)(t + 0x54) = 0;
    *(s32*)(t + 0x58) = 0;
    *(s32*)(t + 0x5C) = 0;
    *(s32*)(t + 0x60) = 0;
    *(s32*)(t + 0x64) = 0;
    *(s32*)(t + 0x68) = 0;
}
