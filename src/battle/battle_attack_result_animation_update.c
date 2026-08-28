#include "fft/battle.h"

extern s32 battle_store_target_stats_pointer_data(u8 misc_id);
extern void func_8017EC18(u8 misc_id, void* arg);
extern void battle_set_map_coords_after_death_dismount(battle_misc_data_t* unit);
extern void battle_jump_to_post_action_display(u8 id);
extern void battle_update_display_by_misc_id(u8 id);

void battle_attack_result_animation_update(battle_misc_data_t* unit) {
    s32 result;

    result = battle_store_target_stats_pointer_data(unit->battle_data->misc_unit_id);
    unit->pending_attack_result = result;
    if (result == -1) {
        func_8017EC18(unit->battle_data->misc_unit_id, &unit->dismount_x);
        battle_set_map_coords_after_death_dismount(unit);
    }
    battle_jump_to_post_action_display(unit->unit_id);
    battle_update_display_by_misc_id(unit->unit_id);
}
