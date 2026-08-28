#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(u32 battle_id);
extern void main_set_svector(s16* destination, u32 x, u32 y, u32 z);
extern void check_direct_weapon_trajectory(u32 attacker_id, s16* target_position,
    u32 target_id);

s32 battle_prepare_single_target_trajectory(u32 attacker_id, u32 target_id) {
    battle_misc_data_t* attacker;
    battle_misc_data_t* target;
    s16 target_position[4];

    attacker = battle_get_unit_misc_data_by_battle_id(attacker_id & 0xFFFF);
    target = battle_get_unit_misc_data_by_battle_id(target_id & 0xFFFF);
    if (target != 0) {
        main_set_svector(target_position, target->map_x, target->map_y, target->map_z);
        check_direct_weapon_trajectory(attacker_id, target_position, target_id);
        if (attacker != 0) {
            attacker->target_count = 1;
            attacker->target_list[0] = target_id;
            return 1;
        }
    }
    return 0;
}
