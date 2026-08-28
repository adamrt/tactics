#include "psx/types.h"

extern volatile u32* D_800741B4;
extern void open_bin_libpress_timeout(const char* tag);
extern const char D_80067060[];

/* OPEN.BIN MDEC in sync - spin until the MDEC input FIFO drains, reporting a
 * timeout through the library's diagnostic dump when the counter expires. */
s32 open_bin_mdec_in_sync(void) {
    volatile s32 timeout = 0x100000;

    while (*D_800741B4 & 0x20000000) {
        if (--timeout == -1) {
            open_bin_libpress_timeout(D_80067060);
            return -1;
        }
    }
    return 0;
}
