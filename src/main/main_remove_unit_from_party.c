#include "psx/types.h"

extern u8 g_party_slot_base;

void main_remove_unit_from_party(u32 index) {
    (&g_party_slot_base)[index << 8] = 0xff;
}
