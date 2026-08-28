#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_ability_animation_flags[];
extern u8 g_ability_charge_animation_sets[];
extern void battle_store_unit_animation_facing(s32 animation, s32 facing, battle_misc_data_t* unit);

void battle_start_ability_charge_animation(battle_misc_data_t* unit) {
    u8 animation;

    animation = g_ability_charge_animation_sets[g_ability_animation_flags[unit->used_ability_id * 3] * 2];
    if (animation != 0) {
        /* facing is passed sign-extended (lh) here. */
        battle_store_unit_animation_facing(animation, *(s16*)&unit->facing, unit);
    }
}
