#include "psx/types.h"

void battle_fill_text_field_with_terminators(u8* text) {
    s32 index;
    u8* cursor = text;

    for (index = 0; index < 16; index++) {
        *cursor++ = 0xfe;
    }
}
