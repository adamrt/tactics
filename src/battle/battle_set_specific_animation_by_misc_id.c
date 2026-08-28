#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void battle_store_unit_animation_facing(u32 animation, s16 facing, u8* unit);

void battle_set_specific_animation_by_misc_id(u32 misc_id, u32 animation) {
    battle_misc_data_t* unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);
    if (unit != 0)
        battle_store_unit_animation_facing(animation, unit->facing, (u8*)unit);
}
