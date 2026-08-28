#include "psx/types.h"

extern volatile u32* D_80074194;
extern void open_bin_libpress_timeout(const char* tag);
extern const char D_80067070[];

/* OPEN.BIN MDEC out sync - spin until the MDEC output FIFO empties, reporting
 * a timeout through the library's diagnostic dump when the counter expires. */
s32 open_bin_mdec_out_sync(void) {
    volatile s32 timeout = 0x100000;

    while (*D_80074194 & 0x01000000) {
        if (--timeout == -1) {
            open_bin_libpress_timeout(D_80067070);
            return -1;
        }
    }
    return 0;
}
