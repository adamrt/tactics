#include "fft/battle.h"

extern u8* battle_get_screen_data_ptr_by_misc_id(u32 misc_id);

void battle_copy_misc_unit_screen_location(u32 misc_id,
    battle_real_coords_t* destination) {
    s16* screen_data;

    screen_data = (s16*)battle_get_screen_data_ptr_by_misc_id(misc_id);
    destination->x = screen_data[0];
    destination->z = screen_data[1];
    destination->y = screen_data[2];
}
