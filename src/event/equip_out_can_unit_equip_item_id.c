#include "psx/types.h"

extern u8* g_equip_unit_data[];

extern s32 equip_out_get_item_type_from_item_number(s32 item);
extern void equip_init_bit_reader_1(const u8* data);
extern s32 equip_get_item_type(s32 item_id);
extern s32 equip_read_primary_bits(s32 arg0);

s32 equip_out_can_unit_equip_item_id(s16 unit_index, s32 item) {
    s32 item_id = item & 0x3FF;
    s32 result;

    if (item_id == 0) {
        return 1;
    }
    if (equip_out_get_item_type_from_item_number(item_id) == 5) {
        return -1;
    }
    equip_init_bit_reader_1(g_equip_unit_data[unit_index] + 0x70);
    equip_read_primary_bits(equip_get_item_type(item_id));
    if (equip_read_primary_bits(1) == 0) {
        result = -1;
    } else {
        result = 1;
    }
    return result;
}
