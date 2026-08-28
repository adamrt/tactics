#include "psx/types.h"

extern u8* g_equip_unit_data[];
extern void bcopy(const void* source, void* destination, u32 size);

void equip_copy_unit_data_to_compare_slot(void) {
    bcopy(g_equip_unit_data[0], g_equip_unit_data[1], 0x7a);
}
