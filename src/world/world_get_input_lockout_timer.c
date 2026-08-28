#include "psx/types.h"

extern u8 D_8018C192;

/* Countdown maintained by 0x80113580; while it is non-zero the formation
   screen's per-frame handler returns before reading controller input. */
s32 world_get_input_lockout_timer(void) {
    return D_8018C192;
}
