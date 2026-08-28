#include "psx/types.h"

/* Widen `count` bytes at `src` into halfwords at `dst`. */
void battle_widen_bytes_to_halfwords(s16* dst, u8* src, s32 count) {
    s32 i;
    char unused[8];

    i = 0;
    if (count > 0) {
        do {
            *dst = *src++;
            i += 1;
            dst += 1;
        } while (i < count);
    }
}
