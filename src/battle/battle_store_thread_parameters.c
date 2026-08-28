#include "psx/types.h"

extern u8* g_event_threads;

typedef struct {
    s32 a; /* 0x0 */
    s32 b; /* 0x4 */
    s32 c; /* 0x8 */
    s32 d; /* 0xC */
} ThreadParams;

void battle_store_thread_parameters(s32 slot, s32 a, s32 b, s32 c, s32 d) {
    ThreadParams* p = (ThreadParams*)(g_event_threads + (slot << 10));
    p->a = a;
    p->b = b;
    p->c = c;
    p->d = d;
}
