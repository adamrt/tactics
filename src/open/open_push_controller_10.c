#include "psx/types.h"

extern u32 g_open_runtime_flags;
extern s32 g_open_current_controller_index;
extern s32 g_open_controller_handler_indices[];
extern s32 g_open_vsync_mode;

extern void open_initialize_screen_environments(s32 mode);
extern void func_8006e2f0(void);

void open_push_controller_10(void) {
    s32 controller;

    g_open_runtime_flags &= ~0x3000;
    open_initialize_screen_environments(1);
    g_open_runtime_flags |= 0x40000;
    func_8006e2f0();

    controller = g_open_current_controller_index;
    g_open_vsync_mode = 2;
    g_open_controller_handler_indices[controller] = 10;
    g_open_current_controller_index = controller + 1;
}
