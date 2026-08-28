#include "psx/types.h"

void require_fill_string_buffer_fe(u8* data) {
    u8 value = 0xfe;
    s32 index;

    for (index = 15; index >= 0; index--) {
        *data++ = value;
    }
}
