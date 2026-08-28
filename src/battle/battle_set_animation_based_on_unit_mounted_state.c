#include "fft/battle.h"

extern s32 battle_validate_float_fly_movement(battle_misc_data_t* unit);
extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u8 misc_id);
extern void battle_store_unit_animation_facing(s32 animation, s16 facing,
    battle_misc_data_t* unit);

void battle_set_animation_based_on_unit_mounted_state(battle_misc_data_t* unit) {
    s32 anim;
    s32 s1v;
    s32 fv;
    battle_misc_data_t* other;

    anim = 0x32;
    if (unit->mount_rider_value != 1) {
        fv = battle_validate_float_fly_movement(unit) & 0xFF;
        if (fv < 0)
            goto else_branch;
        if (fv < 2) {
            s1v = 2;
            if (unit->mount_rider_value == 2) {
                other = battle_get_unit_misc_data_by_misc_id(unit->mount_rider_id);
                if (other != 0) {
                    battle_store_unit_animation_facing(0x32, (s16)unit->facing, other);
                }
            }
        } else {
            goto else_branch;
        }
        goto after;
    else_branch:
        s1v = 9;
    after:;
        if (s1v == 0) {
            return;
        }
        anim = s1v;
    }
    battle_store_unit_animation_facing(anim, (s16)unit->facing, unit);
}
