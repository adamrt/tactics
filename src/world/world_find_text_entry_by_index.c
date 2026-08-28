#include "psx/types.h"

/* Advance past `count` line terminators in a shift-JIS style byte stream. */
u8* world_find_text_entry_by_index(u8* p, s16 count) {
    u8 c;

    while (count != 0) {
        c = *p++;
        if (c >= 0xD0) {
            if (c < 0xE0) {
                p++;
            } else if (c >= 0xFE) {
                count--;
            }
        }
    }
    return p;
}
