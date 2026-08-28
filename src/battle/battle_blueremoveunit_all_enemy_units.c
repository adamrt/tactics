#include "fft/battle.h"

extern s32 battle_does_misc_unit_id_exist(s32 misc_id);
extern s32 battle_get_battle_unit_index_by_misc_id(s32 misc_id);
extern battle_stats_t* battle_get_battle_stats_from_battle_id(s32 index);
extern battle_stats_t* find_unit_by_id(u8 unit_id, s32* out_index);
extern void battle_prepare_misc_unit_palette_modulation(s32 misc_id, s32 mode,
    s32 r, s32 g, s32 b);

void battle_blueremoveunit_all_enemy_units(void) {
    s32 i;
    s32 idx;
    s32 out_index;
    battle_stats_t* stats;
    battle_stats_t* found;

    i = 0;
    do {
        if (battle_does_misc_unit_id_exist(i) != 0) {
            idx = battle_get_battle_unit_index_by_misc_id(i);
            if (idx != -1) {
                stats = battle_get_battle_stats_from_battle_id(idx);
                found = find_unit_by_id(stats->unit_id, &out_index);
                if ((found->initial_team_flags & BATTLE_TEAM_MASK) && out_index != -2) {
                    battle_prepare_misc_unit_palette_modulation(i, 2, -0x1F, -0x1F, 0);
                }
            }
        }
        i++;
    } while (i < 0x15);
}
