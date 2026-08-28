#include "psx/types.h"
extern void bcopy(void* dst, void* src, s32 n);
extern s16 g_bunit_selected_unit_index;
extern u16 D_801CF452;
extern u8* g_bunit_unit_data[];
extern u8 D_801CE8FC[];
extern u8 D_801CE944[];
extern u8 D_801CE964[];
extern s32 D_801CF4C4;
extern s32 D_801CF4D8;
extern s32 D_801CF4EC;
extern s32 D_801CF500;
void bunit_copy_selected_unit_data(void) {
    /* The retail code reads the index unsigned here (lhu) and signed below (lh). */
    s32 idx = *(u16*)&g_bunit_selected_unit_index;
    u8* p = g_bunit_unit_data[(s16)idx];
    D_801CF452 = idx;
    bcopy(p, D_801CE8FC, 0x22);
    bcopy(g_bunit_unit_data[g_bunit_selected_unit_index] + 0x22, D_801CE944, 0xE);
    bcopy(g_bunit_unit_data[g_bunit_selected_unit_index] + 0x30, D_801CE964, 0x40);
    D_801CF4C4 = 1;
    D_801CF4D8 = 1;
    D_801CF4EC = 1;
    D_801CF500 = 1;
}
