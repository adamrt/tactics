#include "psx/types.h"

extern s32 g_world_menu_thread_running_status;
extern void* g_world_menu_thread_menu_data;
extern s32 world_check_thread_running_status(s32 thread_id);
extern void world_initialize_thread(s32 thread_id, void (*entry)(void));
extern void world_store_thread_function_parameters(s32 thread_id, void* arg0, s32 arg1, s32 arg2);

s32 world_run_menu_thread(s32 thread_id, u8* arg) {
    s32 status;
    if (g_world_menu_thread_running_status == 0) {
        if (world_check_thread_running_status(thread_id) != 0) {
            return 1;
        }
        {
            void (*fn)(void) = *(void (**)(void))(arg + 0x28);
            g_world_menu_thread_menu_data = arg;
            world_initialize_thread(thread_id, fn);
        }
        world_store_thread_function_parameters(thread_id, g_world_menu_thread_menu_data, 0, 0);
        g_world_menu_thread_running_status = 1;
        return 1;
    }
    status = world_check_thread_running_status(thread_id);
    g_world_menu_thread_running_status = status;
    return status;
}
