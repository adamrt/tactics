#include "psx/gpu.h"
#include "psx/types.h"

extern u8 D_801EC8F4;
extern s16 g_bunit_clut_id;

u8* bunit_calculate_next_graphic_clut_id(u8* arg0) {
    if (D_801EC8F4 != 0) {
        g_bunit_clut_id = GetClut(arg0[6] << 4, arg0[7] | (arg0[5] << 8));
    } else {
        g_bunit_clut_id = GetClut(arg0[3] << 4, arg0[4] | (arg0[2] << 8));
    }
    return arg0 + arg0[1];
}
