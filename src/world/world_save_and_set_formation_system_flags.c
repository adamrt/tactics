#include "psx/types.h"

extern u32 g_system_flags;
extern u32 g_world_saved_system_flags;

void world_save_and_set_formation_system_flags(void) {
    g_world_saved_system_flags = g_system_flags;
    g_system_flags |= 0x3e70;
}
