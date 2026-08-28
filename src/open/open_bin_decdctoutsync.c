#include "psx/types.h"

extern void open_bin_mdec_out_sync(void);

void open_bin_decdctoutsync(void) {
    open_bin_mdec_out_sync();
}
