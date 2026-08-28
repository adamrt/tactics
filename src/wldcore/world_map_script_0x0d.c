#include "psx/types.h"

extern u16 g_world_script_ip;

void world_map_script_0x0d(void) {
    u16* p = &g_world_script_ip;
    *p += 1;
}
