#include "psx/types.h"

extern void open_bin_mdec_in(s32*, u16);

void open_bin_decdctin(s32* arg0, s32 arg1) {
    if (arg1 & 1) {
        *arg0 = *arg0 & 0xF7FFFFFF;
    } else {
        *arg0 = *arg0 | 0x08000000;
    }
    if (arg1 & 2) {
        *arg0 = *arg0 | 0x02000000;
    } else {
        *arg0 = *arg0 & 0xFDFFFFFF;
    }
    open_bin_mdec_in(arg0, (u16)*arg0);
}
