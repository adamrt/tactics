#include "psx/types.h"

void wldcore_set_display_rect(s32 buffer_index, s16* rect) {
    rect[2] = 0x100;
    rect[0] = 0;
    rect[3] = 0xEE;
    if (buffer_index == 0) {
        rect[1] = 0;
    } else {
        rect[1] = 0xF0;
    }
}
