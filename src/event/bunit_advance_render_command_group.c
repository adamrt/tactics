#include "psx/types.h"

u8* bunit_advance_render_command_group(u8* arg0) {
    s32 n;
    s32 t = arg0[0];
    if (t == 1) {
        n = arg0[4] + 1;
    } else if (t == 2) {
        n = arg0[4] + arg0[5] + 1;
    } else {
        n = 1;
    }
    n -= 1;
    if (n != -1) {
        do {
            n -= 1;
            arg0 += arg0[1];
        } while (n != -1);
    }
    return arg0;
}
