#include "psx/types.h"

extern s32 g_world_menu_thread_running_status;
extern s32 world_run_menu_thread(s32 thread_id, u8* arg);

s32 world_run_menu_thread_set_field_38(s32 thread_id, u8* arg, s16 value) {
    if (g_world_menu_thread_running_status == 0) {
        *(s16*)(arg + 0x38) = value;
    }
    return world_run_menu_thread(thread_id, arg);
}
