#include "fft/battle.h"

extern void main_set_svector(s16* destination, s32 x, s32 y, s32 z);

void battle_copy_misc_data_xyz_values(s16* destination,
    const battle_misc_data_t* misc_data) {
    /* mounted_height_offset is read signed (lh) here. */
    main_set_svector(destination,
        misc_data->screen_x + misc_data->effect_vector_2_x + misc_data->effect_vector_x,
        misc_data->screen_z + misc_data->effect_vector_2_z + misc_data->effect_vector_z + *(s16*)&misc_data->mounted_height_offset,
        misc_data->screen_y + misc_data->effect_vector_2_y + misc_data->effect_vector_y);
}
