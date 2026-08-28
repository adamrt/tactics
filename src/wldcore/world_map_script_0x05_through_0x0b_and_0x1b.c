#include "psx/types.h"

extern u16 g_world_script_ip;

void world_map_script_0x05_through_0x0b_and_0x1b(void) {
    u16* p = &g_world_script_ip;
    *p += 2;
}
