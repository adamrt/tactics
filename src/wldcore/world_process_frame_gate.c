#include "psx/types.h"

extern s32 g_system_flags;
extern s32 g_previous_system_flags;
extern void world_initialize_core(void);

/* Reinitialize WLDCORE when system-flag bit 1 transitions from set to clear. */
void world_process_frame_gate(void) {
    if ((g_system_flags & 2) == 0 && (g_previous_system_flags & 2) != 0) {
        world_initialize_core();
    }
    g_previous_system_flags = g_system_flags;
}
