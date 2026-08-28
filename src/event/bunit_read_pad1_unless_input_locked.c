#include "psx/types.h"

extern s32 main_read_controller_input(s32 port);
extern s32 bunit_get_input_lock_timer(void);

/* BUNIT.OUT 001c3150 - Return the pad-1 input, or 0 while the input lock timer is active. */
s32 bunit_read_pad1_unless_input_locked(void) {
    s32 input;

    input = main_read_controller_input(0);
    if (bunit_get_input_lock_timer() != 0) {
        input = 0;
    }
    return input;
}
