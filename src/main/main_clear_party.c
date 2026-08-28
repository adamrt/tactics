#include "psx/types.h"

extern u8 g_party_slot_base;

void main_clear_party(void) {
    u8 value = 0xff;
    s32 offset = 0x1300;

    do {
        (&g_party_slot_base)[offset] = value;
        offset -= 0x100;
    } while (offset >= 0);
}
