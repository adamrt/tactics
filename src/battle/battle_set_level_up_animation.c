#include "fft/battle.h"

enum {
    LEVEL_UP_ANIMATION_SUBMERGED = 0x09,
    LEVEL_UP_ANIMATION_WALKING = 0x1c,
    LEVEL_UP_ANIMATION_SMALL_HOPS = 0x1d,
};

extern s32 battle_validate_float_fly_movement(battle_misc_data_t* unit);
extern void battle_store_unit_animation_facing(s32 animation, s32 facing,
    battle_misc_data_t* unit);

void battle_set_level_up_animation(battle_misc_data_t* unit) {
    s32 movement_type;
    /* Pin: the animation id is built directly in $a0 (li a0,N per arm and
     * the a0 reload in the first call's delay slot); unpinned GCC homes it
     * in $s0 and adds moves. */
    register s32 animation __asm__("$4");

    animation = LEVEL_UP_ANIMATION_SMALL_HOPS;
    if (unit->mount_rider_value == 1) {
        goto store_animation;
    }

    movement_type = (u8)battle_validate_float_fly_movement(unit);
    if (movement_type == 1) {
        goto use_small_hops;
    }
    if (movement_type >= 2) {
        goto check_submerged;
    }
    animation = LEVEL_UP_ANIMATION_WALKING;
    if (movement_type == 0) {
        goto store_animation;
    }
    goto out;

check_submerged:
    animation = LEVEL_UP_ANIMATION_SUBMERGED;
    if (movement_type == 2) {
        goto store_animation;
    }
    goto out;

use_small_hops:
    animation = LEVEL_UP_ANIMATION_SMALL_HOPS;

store_animation:
    /* The target reads facing as a signed halfword (lh). */
    battle_store_unit_animation_facing(animation, *(s16*)&unit->facing, unit);

out:
    return;
}
