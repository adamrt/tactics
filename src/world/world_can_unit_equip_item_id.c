#include "fft/data.h"

extern s32 world_get_item_type_from_item_number(s32 item_id);
extern void world_store_combined_bit_value_pointer(u8* ptr);
extern s32 world_get_item_type(s32 item_id);
extern s32 read_stored_bits(s32 count);

s32 world_can_unit_equip_item_id(s16 unit_index, s32 item_id) {
    s32 id = item_id & WORLD_ITEM_ID_MASK;
    s32 result;

    if (id == 0) {
        return 1;
    }
    if (world_get_item_type_from_item_number(id) == 5) {
        return -1;
    }
    world_store_combined_bit_value_pointer(g_world_formation_unit_pointers[unit_index]->equippable_item_types);
    read_stored_bits(world_get_item_type(id));
    if (read_stored_bits(1) == 0) {
        result = -1;
    } else {
        result = 1;
    }
    return result;
}
