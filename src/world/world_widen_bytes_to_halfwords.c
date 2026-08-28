#include "psx/types.h"

s32 world_widen_bytes_to_halfwords(u16* destination, const u8* source) {
    s32 count = 0;
    s32 terminator = 0xFF;

loop:
    if (*source == terminator) {
        return count;
    }
    *destination = *source;
    source++;
    count++;
    destination++;
    goto loop;
}
