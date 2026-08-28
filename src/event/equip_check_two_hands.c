#include "psx/types.h"

extern u8* g_equip_unit_data[];

s32 equip_check_two_hands(s16 unit_id) {
    return g_equip_unit_data[unit_id][0x76] & 0x02;
}
