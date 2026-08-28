#include "psx/types.h"
extern u8* g_last_unit_misc_data;
s32 battle_count_units_from_misc_data(void) {
    s32 count = 0;
    u8* unit = g_last_unit_misc_data;
    if (unit != 0) {
        do {
            unit = *(u8**)unit;
            count++;
        } while (unit != 0);
    }
    return count;
}
