#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_y;
extern s32 g_battle_cursor_z;
extern s32 g_battle_status_flag;
extern s32 g_battle_casting_unit_id;
extern s32 g_battle_casting_misc_id;
extern battle_misc_data_t* battle_get_misc_data_at_map_coords_2(s32, s32, s32);
extern void battle_open_active_unit_idle_action_menu(void);
extern void func_800712D8(void);
extern void open_non_active_unit_action_menu(void);

void battle_call_idle_action_menu(void) {
    battle_misc_data_t* misc;

    misc = battle_get_misc_data_at_map_coords_2(g_battle_cursor_x, g_battle_cursor_y, g_battle_cursor_z);
    if (misc == 0) {
        return;
    }
    g_battle_casting_unit_id = misc->unit_id;
    if (g_battle_status_flag == 0 && misc->unit_id == g_battle_casting_misc_id) {
        if ((misc->team_flags & 8) != 0) {
            battle_open_active_unit_idle_action_menu();
        } else {
            func_800712D8();
        }
    } else {
        open_non_active_unit_action_menu();
    }
}
