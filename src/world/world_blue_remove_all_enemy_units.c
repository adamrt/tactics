#include "fft/battle.h"

extern s32 battle_does_misc_unit_id_exist(s32 misc_id);
extern s32 get_unit_id_from_misc_id(s32 misc_id);
extern battle_stats_t* get_battle_stats_pointer(s32 unit_index);
extern battle_stats_t* find_unit_by_id(u8 unit_id, s32* resolved_id);
extern void battle_prepare_misc_unit_palette_modulation(s32 misc_id, s32 mode, s32 x, s32 y, s32 z);

void world_blue_remove_all_enemy_units(void) {
    s32 resolved_id;
    s32 unit_index;
    s32 misc_id;

    misc_id = 0;
    do {
        if (battle_does_misc_unit_id_exist(misc_id) != 0) {
            unit_index = get_unit_id_from_misc_id(misc_id);
            if (unit_index != -1 && (find_unit_by_id(get_battle_stats_pointer(unit_index)->unit_id, &resolved_id)->initial_team_flags & 0x30) != 0 && resolved_id != -2) {
                battle_prepare_misc_unit_palette_modulation(misc_id, 2, -0x1f, -0x1f, 0);
            }
        }
        misc_id++;
    } while (misc_id < 21);
}
