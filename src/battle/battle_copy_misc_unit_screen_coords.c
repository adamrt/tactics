#include "psx/types.h"

extern u8* battle_get_screen_data_ptr_by_misc_id(u32 misc_id);

void battle_copy_misc_unit_screen_coords(u32 misc_id, u16* screen_coords) {
    u16* screen_data;

    screen_data = (u16*)battle_get_screen_data_ptr_by_misc_id(misc_id);
    if (screen_data != (u16*)-1) {
        screen_coords[0] = screen_data[0];
        screen_coords[1] = screen_data[1];
        screen_coords[2] = screen_data[2];
    }
}
