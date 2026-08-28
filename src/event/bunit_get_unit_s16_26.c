#include "fft/bunit.h"

extern bunit_unit_data_t* g_bunit_unit_data[];

s32 bunit_get_unit_s16_26(s32 unit_id) {
    return *(s16*)((u8*)g_bunit_unit_data[unit_id] + 0x26);
}
