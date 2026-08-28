#include "psx/types.h"

extern u32 D_80074078[];
extern u32 D_8007407C[16];
extern u32 D_800740BC[16];
extern u32 D_800740FC[];
extern void open_bin_mdec_in(u32* packet, u32 words);

/* OPEN.BIN DecDCTPutEnv - install the caller supplied quantisation and IDCT
 * tables into the library's cache and push both of them to the MDEC. */
u32* open_bin_decdctputenv(u32* env) {
    u32* src;
    u32* dst;
    s32 i;

    src = env;
    dst = D_8007407C;
    i = 15;
    do {
        *dst++ = *src++;
    } while (--i != -1);

    dst = D_800740BC;
    src = env + 16;
    i = 15;
    do {
        *dst++ = *src++;
    } while (--i != -1);

    open_bin_mdec_in(D_80074078, 0x20);
    open_bin_mdec_in(D_800740FC, 0x20);
    return env;
}
