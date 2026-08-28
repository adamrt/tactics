#include "psx/types.h"

void main_clear_byte_data(u8* destination, s32 count) {
    s32 index = 0;

    while (index < count) {
        *destination++ = 0;
        index++;
    }
}
