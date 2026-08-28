#include "psx/types.h"

extern s32 g_world_script_flags;
extern s32 g_world_script_data_ptr;
extern u16 g_world_script_ip;
extern s32 g_world_script_value;

void world_map_script_0x22(void) {
    g_world_script_flags |= 0x401;
    g_world_script_value = ((u16*)g_world_script_data_ptr)[g_world_script_ip];
}
