#include "psx/types.h"

extern void open_bin_mdec_in_sync(void);
extern volatile u32* D_800741B8;
extern volatile u32* D_80074180;
extern volatile u32* D_80074184;
extern volatile u32* D_800741B0;
extern volatile u32* D_80074188;

void open_bin_mdec_in(u32* arg0, u32 arg1) {
    open_bin_mdec_in_sync();
    *D_800741B8 |= 0x88;
    *D_80074180 = (u32)(arg0 + 1);
    *D_80074184 = ((arg1 >> 5) << 16) | 0x20;
    *D_800741B0 = arg0[0];
    *D_80074188 = 0x01000201;
}
