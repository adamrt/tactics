#include "psx/types.h"

extern s32 g_world_menu_thread_result;

s32 world_take_and_clear_menu_thread_result(void) {
    s32 result = g_world_menu_thread_result;

    g_world_menu_thread_result = 0;
    return result;
}
