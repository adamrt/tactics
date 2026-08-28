#include "psx/types.h"

extern s32 world_get_8018df7c_or_one(void);
extern s16 g_world_tutorial_wait_timer;
extern u8* g_world_tutorial_command_ptr;

void world_handle_tutorial_command_wait(void) {
    g_world_tutorial_wait_timer -= world_get_8018df7c_or_one();
    if (g_world_tutorial_wait_timer <= 0) {
        g_world_tutorial_wait_timer = 0;
        g_world_tutorial_command_ptr++;
    }
}
