#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_z;
extern s32 g_battle_cursor_y;
extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(u8);
extern void battle_move_cursor_to_unit(s32);

void battle_x_y_data_gathering_for_attacks(battle_misc_data_t* unit) {
    battle_stats_t* bd;

    bd = unit->battle_data;
    if (bd->action_reaction_id == 5) {
        g_battle_cursor_x = bd->action_target_x;
        g_battle_cursor_z = unit->battle_data->action_target_elevation;
        g_battle_cursor_y = unit->battle_data->action_target_y;
        return;
    }
    battle_move_cursor_to_unit((s32)battle_get_unit_misc_data_by_battle_id(bd->action_target_id));
}
