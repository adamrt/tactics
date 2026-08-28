#include "psx/types.h"

void debugchr_fill_16_bytes_with_fe(u8* output) {
    s32 i;
    u8 value;

    value = 0xfe;
    for (i = 15; i >= 0; i--) {
        *output++ = value;
    }
}
