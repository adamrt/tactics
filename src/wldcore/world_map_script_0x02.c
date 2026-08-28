#include "psx/types.h"

extern void wldcore_store_script_data_into_r4_and_r5(s32* out_id, s32* out_value);
extern s32 world_get_script_variable(s32 variable_id);
extern s32 g_world_script_flags;

/* World Map Script 0x02 - if variable < value, set flag bit 0x2. */
void world_map_script_0x02(void) {
    s32 variable_id;
    s32 value;
    s32* flags;

    wldcore_store_script_data_into_r4_and_r5(&variable_id, &value);
    if (world_get_script_variable(variable_id) < value) {
        flags = &g_world_script_flags;
        *flags |= 0x2;
    }
}
