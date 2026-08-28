#include "psx/types.h"

void main_copy_byte_data(const u8* source, u8* destination, s32 count) {
    s32 index = 0;

    while (index < count) {
        *destination++ = *source++;
        index++;
    }
}
