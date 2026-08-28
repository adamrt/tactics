#include "psx/types.h"

extern u8 g_bunit_input_lock_timer;

s32 bunit_get_input_lock_timer(void) {
    return g_bunit_input_lock_timer;
}
