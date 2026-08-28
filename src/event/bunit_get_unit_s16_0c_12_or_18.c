#include "psx/types.h"

extern u8* g_bunit_unit_data[];

s16 bunit_get_unit_s16_0c_12_or_18(s32 arg0, s32 arg1) {
    u8 mode;
    u8* entry;

    mode = *(u8*)0x801CF557;
    if (mode == 0) {
        entry = g_bunit_unit_data[arg0];
        arg1 = *(s16*)(entry + 0xC);
    } else if (mode == 1) {
        entry = g_bunit_unit_data[arg0];
        arg1 = *(s16*)(entry + 0x12);
    } else if (mode == 2) {
        entry = g_bunit_unit_data[arg0];
        arg1 = *(s16*)(entry + 0x18);
    }
    *(s16*)0x801EB204 = arg1;
    return (s16)arg1;
}
