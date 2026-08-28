#include "psx/types.h"

extern s32 g_world_script_data_ptr;
extern u16 g_world_script_ip;

void wldcore_store_script_data_into_r4_and_r5(s32* out1, s32* out2) {
    u16* ip = &g_world_script_ip;
    u16 v;

    *out1 = ((u16*)g_world_script_data_ptr)[*ip];
    v = *ip + 1;
    *ip = v;
    *out2 = ((u16*)g_world_script_data_ptr)[v];
    *ip = *ip + 1;
}
