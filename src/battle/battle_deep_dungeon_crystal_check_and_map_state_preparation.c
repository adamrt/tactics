#include "psx/types.h"

extern s32 D_80045978;
extern s32 g_deep_dungeon_map_load_in_progress;

extern s32 battle_count_special_misc_units(void);
extern s32 battle_get_script_variable(s32);
extern void battle_set_script_variable(s32, s32);
extern s32 battle_load_map_data_stage_0x75(void);

s32 battle_deep_dungeon_crystal_check_and_map_state_preparation(void) {
    s32 count;
    s32 var;

    if (D_80045978 == 4) {
        if (g_deep_dungeon_map_load_in_progress == 0) {
            count = battle_count_special_misc_units();
            if (count >= 5) {
                count = 4;
            }
            var = battle_get_script_variable(0x70);
            if (count != var) {
                battle_set_script_variable(0x70, count);
                if (battle_load_map_data_stage_0x75() != 0) {
                    g_deep_dungeon_map_load_in_progress = 1;
                } else {
                    battle_set_script_variable(0x70, var);
                }
            }
        }
        return g_deep_dungeon_map_load_in_progress;
    }
    return 0;
}
