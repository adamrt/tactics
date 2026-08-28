#include "psx/types.h"

extern void open_bin_mdec_in_sync(void);

void open_bin_decdctinsync(void) {
    open_bin_mdec_in_sync();
}
