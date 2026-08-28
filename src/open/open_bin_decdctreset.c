#include "psx/types.h"

extern void ResetCallback(void);
extern void opening_open_bin_mdec_reset(s32 mode);

/* OPEN.BIN DecDCTReset - wrapper around the DCT reset routine that also
 * clears the BIOS callback table when initializing from scratch. */
void open_bin_decdctreset(s32 mode) {
    if (mode == 0) {
        ResetCallback();
    }
    opening_open_bin_mdec_reset(mode);
}
