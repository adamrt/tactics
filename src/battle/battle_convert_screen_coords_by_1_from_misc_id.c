#include "psx/types.h"

extern u8* battle_get_screen_data_ptr_by_misc_id(u32 misc_id);
extern void convert_screen_coords_modify_by_1(u8* screen_data, s16* coords);

void battle_convert_screen_coords_by_1_from_misc_id(u32 misc_id, s16* coords) {
    convert_screen_coords_modify_by_1(battle_get_screen_data_ptr_by_misc_id(misc_id & 0xffff), coords);
}
