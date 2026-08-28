#include "psx/types.h"

extern volatile u32* D_800741B4;
extern volatile u32* D_80074188;
extern volatile u32* D_80074194;
extern u32 D_80074078[];
extern u32 D_800740FC[];
extern const char D_80067044[];
extern void open_bin_mdec_in(u32* packet, u32 words);
extern void func_8002232C(const char* fmt, ...);

/* OPEN.BIN MDEC reset - drop the decoder back to a known state.  Mode 0 also
 * re-uploads the cached quantisation and IDCT tables. */
void opening_open_bin_mdec_reset(s32 mode) {
    switch (mode) {
    case 0:
        *D_800741B4 = 0x80000000;
        *D_80074188 = 0;
        *D_80074194 = 0;
        *D_800741B4 = 0x60000000;
        open_bin_mdec_in(D_80074078, 0x20);
        open_bin_mdec_in(D_800740FC, 0x20);
        break;
    case 1:
        *D_800741B4 = 0x80000000;
        *D_80074188 = 0;
        *D_80074194 = 0;
        *D_80074194;
        *D_800741B4 = 0x60000000;
        break;
    default:
        func_8002232C(D_80067044, mode);
        break;
    }
}
