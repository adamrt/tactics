#include "psx/types.h"

extern s32 (*g_event_threads)[256];

s32 equip_get_thread_field_0x12(s32 thread_id) {
    return g_event_threads[thread_id][0x12];
}
