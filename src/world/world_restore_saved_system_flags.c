#include "psx/types.h"

extern u32 g_system_flags;
extern u32 g_world_saved_system_flags;

void world_restore_saved_system_flags(void) {
    g_system_flags = g_world_saved_system_flags;
}
