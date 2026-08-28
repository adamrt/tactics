#include "fft/battle.h"

void battle_store_unit_animation_facing(u32 animation, s16 facing, u8* unit) {
    battle_misc_data_t* misc = (battle_misc_data_t*)unit;
    animation++;
    misc->requested_animation = animation;
    misc->facing = facing;
}
