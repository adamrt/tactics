#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void battle_store_unit_animation_facing_movement_data(u32 animation,
    s16 facing, u8* unit);

s32 battle_set_animation_from_facing_nibble(u32 misc_id, s32 facing_nibble) {
    battle_misc_data_t* unit;
    s32 animation;
    s16 facing;

    unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);
    if (unit != 0) {
        animation = unit->encoded_animation >> 1;
        facing = facing_nibble << 8;
        unit->facing = facing;
        if (animation < 3) {
            animation = 2;
        }
        battle_store_unit_animation_facing_movement_data(animation, facing, (u8*)unit);
        return misc_id;
    }
    return -1;
}
