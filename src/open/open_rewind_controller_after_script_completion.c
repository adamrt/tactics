#include "psx/types.h"

extern s32 g_open_current_controller_index;
extern u32 g_open_runtime_flags;
extern s32 g_open_vsync_mode;

extern s32 open_initialize_and_dispatch_script_entries(void);

void open_rewind_controller_after_script_completion(void) {
    if (open_initialize_and_dispatch_script_entries() == 0) {
        g_open_vsync_mode = 0;
        g_open_current_controller_index--;
        g_open_runtime_flags ^= 1;
    }
}
