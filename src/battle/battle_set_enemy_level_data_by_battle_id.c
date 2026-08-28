#include "fft/battle.h"
#include "psx/types.h"

extern void battle_set_enemy_level_data(battle_stats_t* stats);
extern battle_stats_t battle_stats[];

s32 battle_set_enemy_level_data_by_battle_id(u32 battle_id) {
    battle_stats_t* stats = &battle_stats[battle_id];

    if (stats->entd_slot != 0xFF)
        return 0;
    if (stats->existence != 0)
        return -1;
    stats->entd_slot = battle_id;
    stats->existence = 1;
    if (stats->team_flags & BATTLE_TEAM_MASK) {
        battle_set_enemy_level_data(stats);
    }
    return 0;
}
