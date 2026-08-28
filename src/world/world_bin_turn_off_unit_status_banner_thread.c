#include "psx/types.h"

extern void world_store_thread_function_parameters(s32 thread_id, s32 a, s32 b, s32 c);

void world_bin_turn_off_unit_status_banner_thread(s32 thread_id) {
    world_store_thread_function_parameters(thread_id, 0, 0, 1);
}
