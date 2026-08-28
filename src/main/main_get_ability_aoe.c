#include "psx/types.h"

extern u8 g_ability_aoe_data;

u32 main_get_ability_aoe(u32 ability_id) {
    u32 result;

    ability_id &= 0xffff;
    if (ability_id < 0x170) {
        result = (&g_ability_aoe_data)[ability_id * 14];
    } else {
        result = 0;
    }
    return result;
}
