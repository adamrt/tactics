#include "psx/types.h"

extern u32 D_8007407C[16];
extern u32 D_800740BC[16];
extern u32 D_80074100[32];

/* OPEN.BIN DecDCTGetEnv - copy the three cached MDEC tables out of the
 * library's private storage into the caller supplied environment block. */
u32* open_bin_decdctgetenv(u32* env) {
    u32* dst;
    u32* src;
    s32 i;

    dst = env;
    src = D_8007407C;
    i = 15;
    do {
        *dst++ = *src++;
    } while (--i != -1);

    dst = env + 16;
    src = D_800740BC;
    i = 15;
    do {
        *dst++ = *src++;
    } while (--i != -1);

    dst = env + 32;
    src = D_80074100;
    i = 31;
    do {
        *dst++ = *src++;
    } while (--i != -1);

    return env;
}
