#include "psx/types.h"

extern u8* g_world_unit_status_staging_data;

void world_clear_unit_status_staging_data(void) {
    s32 unit_index;

    unit_index = 0;
    do {
        *(g_world_unit_status_staging_data + unit_index + 0x39c) = 0;
        *(g_world_unit_status_staging_data + unit_index + 0x3b1) = 0;
        unit_index++;
    } while (unit_index < 21);
}
