#include "psx/types.h"

extern void open_bin_mdec_out_sync(void);
extern u32* g_mdec_ptr_a;
extern u32* g_mdec_ptr_b;
extern u32* g_mdec_ptr_c;
extern u32* g_mdec_ptr_d;

void open_bin_mdec_out(u32 arg0, u32 arg1) {
    open_bin_mdec_out_sync();
    *g_mdec_ptr_a |= 0x88;
    *g_mdec_ptr_b = 0;
    *g_mdec_ptr_c = arg0;
    *g_mdec_ptr_d = ((arg1 >> 5) << 16) | 0x20;
    *g_mdec_ptr_b = 0x01000200;
}
