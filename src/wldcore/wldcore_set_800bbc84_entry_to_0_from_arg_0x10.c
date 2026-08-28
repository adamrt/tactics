#include "psx/types.h"

extern s32 D_800BBC84[];

void wldcore_set_800bbc84_entry_to_0_from_arg_0x10(s32* arg0) {
    s32 index;

    index = arg0[4];
    if (index != -1) {
        D_800BBC84[index * 13] = 0;
    }
}
