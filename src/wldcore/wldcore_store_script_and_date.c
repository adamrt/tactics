#include "psx/types.h"

extern u16* g_world_script_data_ptr;
extern u16 g_world_script_ip;
extern s32 world_get_script_variable(s32 variable_id);

void wldcore_store_script_and_date(s32* out_a, s32* out_b, s32* out_c, s32* out_d) {
    u16* ipp;
    u16 ip;

    ipp = &g_world_script_ip;
    *out_a = g_world_script_data_ptr[*ipp];
    ip = *ipp + 1;
    *ipp = ip;
    *out_b = g_world_script_data_ptr[ip];
    *ipp = *ipp + 1;
    *out_c = world_get_script_variable(0x2E);
    *out_d = world_get_script_variable(0x2F);
}
