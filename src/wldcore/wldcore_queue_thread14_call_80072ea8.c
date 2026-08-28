#include "psx/types.h"

extern s32 g_world_menu_result;

extern void world_store_thread_function_parameters(
    s32 thread_id, s32 function_index, s32 parameter_0, s32 parameter_1);

void wldcore_queue_thread14_call_80072ea8(void) {
    g_world_menu_result = 0x160;
    world_store_thread_function_parameters(14, 0x19, 0xB80B, 0);
}
