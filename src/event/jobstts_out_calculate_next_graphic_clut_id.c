#include "psx/gpu.h"
#include "psx/types.h"

extern u8 D_801FA708;
extern s16 g_jobstts_clut_id;

u8* jobstts_out_calculate_next_graphic_clut_id(u8* arg0) {
    if (D_801FA708 != 0) {
        g_jobstts_clut_id = GetClut(arg0[6] << 4, arg0[7] | (arg0[5] << 8));
    } else {
        g_jobstts_clut_id = GetClut(arg0[3] << 4, arg0[4] | (arg0[2] << 8));
    }
    return arg0 + arg0[1];
}
