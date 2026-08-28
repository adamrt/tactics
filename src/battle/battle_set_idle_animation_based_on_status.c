#include "fft/battle.h"
#include "psx/types.h"

extern u8 battle_movement_validation_float_fly(battle_misc_data_t* unit);
extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(s32 misc_id);
extern void battle_store_unit_animation_facing(s32 anim, s32 facing, battle_misc_data_t* unit);

/* facing is read signed (lh) throughout. */
void battle_set_idle_animation_based_on_status(battle_misc_data_t* unit) {
    s32 anim;
    s32 movement_type;
    s32 walk_speed;
    battle_misc_data_t* mount;

    if (unit->mount_rider_value == 1) {
        battle_store_unit_animation_facing(0x32, *(s16*)&unit->facing, unit);
        return;
    }
    movement_type = battle_movement_validation_float_fly(unit);
    if (movement_type < 0) {
        goto mounted;
    }
    if (movement_type >= 2) {
        goto mounted;
    }
    /* walk_speed and its copy are read together as one word. */
    walk_speed = *(s32*)&unit->walk_speed;
    if (walk_speed >= 0x3000) {
        anim = 0xD;
    } else {
        anim = 0xC;
        if (walk_speed < 0x1401) {
            anim = 0xE;
        }
    }
    if (unit->mount_rider_value == 2) {
        mount = battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
        if (mount != 0) {
            battle_store_unit_animation_facing(0x32, *(s16*)&unit->facing, mount);
        }
    }
    goto done;
mounted:
    walk_speed = *(s32*)&unit->walk_speed;
    if (walk_speed >= 0x3000) {
        anim = 0xA;
    } else {
        anim = 0x9;
        if (walk_speed < 0x1401) {
            anim = 0xB;
        }
    }
done:
    if (anim != 0) {
        battle_store_unit_animation_facing(anim, *(s16*)&unit->facing, unit);
    }
}
