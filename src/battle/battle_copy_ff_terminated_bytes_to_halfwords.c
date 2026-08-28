#include "psx/types.h"

s32 battle_copy_ff_terminated_bytes_to_halfwords(s16* dst, u8* src) {
    s32 count;
    s32 terminator;

    count = 0;
    terminator = 0xFF;
loop:
    if (*src == terminator) {
        return count;
    }
    *dst = *src;
    src += 1;
    count += 1;
    dst += 1;
    goto loop;
}
