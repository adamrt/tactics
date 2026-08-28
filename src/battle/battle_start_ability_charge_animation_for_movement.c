#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_ability_animation_flags[];
extern u8 g_ability_charge_animation_sets[];
extern s32 battle_validate_float_fly_movement(battle_misc_data_t* unit);
extern void battle_store_unit_animation_facing(s32 animation, s32 facing, battle_misc_data_t* unit);

void battle_start_ability_charge_animation_for_movement(battle_misc_data_t* unit) {
    u8 animation;
    u8 movement_type;
    s32 selected_animation;

    animation = g_ability_charge_animation_sets[g_ability_animation_flags[unit->used_ability_id * 3] * 2 + 1];
    if (animation != 0) {
        movement_type = battle_validate_float_fly_movement(unit);
        selected_animation = 9;
        if (movement_type < 2) {
            selected_animation = animation;
        }
        /* facing is read signed (lh) here. */
        battle_store_unit_animation_facing(selected_animation,
            *(s16*)&unit->facing, unit);
    }
}
