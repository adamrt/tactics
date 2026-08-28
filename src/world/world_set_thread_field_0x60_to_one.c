#include "fft/data.h"

void world_set_thread_field_0x60_to_one(s32 thread_id) {
    g_world_threads[thread_id].unk_50[4] = 1;
}
