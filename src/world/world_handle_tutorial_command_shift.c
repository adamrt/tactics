#include "psx/types.h"

extern s32 world_get_8018df7c_or_one(void);
extern u8* g_world_tutorial_command_ptr;
extern s32 g_world_tutorial_command_active;
extern s16 g_world_tutorial_shift_command_bit;

void world_handle_tutorial_command_shift(void) {
    if (g_world_tutorial_command_active != 0) {
        g_world_tutorial_command_active -= world_get_8018df7c_or_one();
        g_world_tutorial_shift_command_bit = 0;
        if (g_world_tutorial_command_active <= 0) {
            g_world_tutorial_command_active = 0;
            ++g_world_tutorial_command_ptr;
        }
    } else {
        g_world_tutorial_command_active = 0x1E;
        g_world_tutorial_shift_command_bit = 1 << *g_world_tutorial_command_ptr;
    }
}
