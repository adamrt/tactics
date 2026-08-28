#include "psx/types.h"

extern s32 g_world_script_data_ptr;
extern u16 g_world_script_ip;
extern s32 g_world_script_flags;
extern s32 world_get_script_variable(s32);

void world_map_script_0x0e(void) {
    u16* ip = &g_world_script_ip;
    u16 idx = *ip;
    u16 value = ((u16*)g_world_script_data_ptr)[idx];
    *ip = idx + 1;
    if (world_get_script_variable(0x2C) < (s32)value) {
        g_world_script_flags |= 2;
    }
}
