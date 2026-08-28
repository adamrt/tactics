#include "psx/types.h"

u8* equip_advance_render_command_group(u8* p) {
    s32 count;

    if (p[0] == 1) {
        count = p[4] + 1;
    } else if (p[0] == 2) {
        count = p[4] + p[5] + 1;
    } else {
        count = 1;
    }
    count -= 1;
    while (count != -1) {
        p += p[1];
        count -= 1;
    }
    return p;
}
