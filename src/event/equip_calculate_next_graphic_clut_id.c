#include "psx/gpu.h"
#include "psx/types.h"

extern u8 g_equip_compact_layout;
extern s16 g_equip_clut_id;

u8* equip_calculate_next_graphic_clut_id(u8* arg0) {
    if (g_equip_compact_layout != 0) {
        g_equip_clut_id = GetClut(arg0[6] << 4, arg0[7] | (arg0[5] << 8));
    } else {
        g_equip_clut_id = GetClut(arg0[3] << 4, arg0[4] | (arg0[2] << 8));
    }
    return arg0 + arg0[1];
}
