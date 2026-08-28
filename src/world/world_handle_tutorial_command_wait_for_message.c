#include "psx/types.h"

extern void world_resume_text_printing(s32);
extern s32 world_check_thread_running_status(s32);
extern s32 g_world_tutorial_command_ptr;

void world_handle_tutorial_command_wait_for_message(void) {
    world_resume_text_printing(0x10);
    if (world_check_thread_running_status(0x10) == 0) {
        g_world_tutorial_command_ptr++;
    }
}
