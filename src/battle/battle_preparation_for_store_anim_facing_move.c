#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_get_script_variable(s32 var_id);
extern void battle_set_animation_from_facing_nibble(s32 misc_id, s32 facing);
extern battle_stats_t* battle_get_battle_stats_from_battle_id(s32 battle_id);
extern s32 battle_get_battle_unit_index_by_misc_id(s32 misc_id);
extern s32 battle_get_unit_misc_id_by_battle_id(s32 battle_id);

void battle_preparation_for_store_anim_facing_move(s32 misc_id, s32 facing) {
    s32 battle_id;
    battle_stats_t* stats;

    if (battle_get_script_variable(0x1FD) == 0) {
        battle_id = battle_get_battle_unit_index_by_misc_id(misc_id);
        if (battle_id >= 0) {
            stats = battle_get_battle_stats_from_battle_id(battle_id);
            if (stats->mount_info != 0) {
                battle_set_animation_from_facing_nibble(
                    battle_get_unit_misc_id_by_battle_id(stats->mount_info & 0x1F),
                    facing & 0xFFFF);
            }
        }
    }
    battle_set_animation_from_facing_nibble(misc_id, facing & 0xFFFF);
}
