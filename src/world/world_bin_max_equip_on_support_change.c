#include "psx/types.h"
extern s32 g_customized_options;
s32 world_bin_max_equip_on_support_change(s16 arg0, s16 arg1) {
    if (arg0 == 0x14 || (g_customized_options & 0x60000000))
        return 0;
    if ((u32)((u16)(arg1 - 0x1C6)) < 8U)
        return 1;
    if (arg1 == 0x1D8 || arg1 == 0x1DC)
        return 1;
    return arg1 == 0x1DD;
}
