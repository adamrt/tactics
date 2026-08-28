#include "psx/types.h"

extern s32 world_get_8018df7c_or_one(void);
extern s32 g_world_tutorial_command_active;
extern u8* g_world_tutorial_command_ptr;
extern s16 g_world_tutorial_wait_time_remaining;

void world_handle_tutorial_command_wait_time(void) {
    if (g_world_tutorial_command_active != 0) {
        g_world_tutorial_wait_time_remaining -= world_get_8018df7c_or_one();
        if (g_world_tutorial_wait_time_remaining < 0) {
            g_world_tutorial_command_active = 0;
            g_world_tutorial_command_ptr += 2;
        }
    } else {
        g_world_tutorial_command_active = 1;
        g_world_tutorial_wait_time_remaining = *(g_world_tutorial_command_ptr + 1);
    }
}
