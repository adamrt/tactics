#include "psx/types.h"

extern void world_clear_some_data_at_r4_and_r5(void* dst, void* unit);
extern void world_get_ability_s_move_and_jump_increase_values(s16 ability_id,
    u16* out);

void world_find_stat_changes_due_to_equipped_abilities(s16* stat_diff,
    s16 old_ability,
    s16 new_ability) {
    u8 buf10[0x28];
    u16 old_stats[0x20];
    u16 new_stats[0x20];

    world_clear_some_data_at_r4_and_r5(buf10, stat_diff);
    world_get_ability_s_move_and_jump_increase_values(old_ability, old_stats);
    world_get_ability_s_move_and_jump_increase_values(new_ability, new_stats);
    stat_diff[0] = new_stats[0] - old_stats[0];
    stat_diff[2] = new_stats[2] - old_stats[2];
}
