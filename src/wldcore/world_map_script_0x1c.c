#include "psx/types.h"

extern void wldcore_store_script_data_into_r4_and_r5(s32* out_id, s32* out_value);
extern void world_set_script_variable(s32 variable_id, s32 value);

/* World Map Script 0x1C - SetVar: read next two script args and set a variable. */
void world_map_script_0x1c(void) {
    s32 variable_id;
    s32 value;

    wldcore_store_script_data_into_r4_and_r5(&variable_id, &value);
    world_set_script_variable(variable_id, value);
}
