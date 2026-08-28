#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_game_state;

extern void battle_stop_game_flow(void);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void set_at_list_active(void);
extern void battle_clear_at_list_active(void);
extern s32 func_80174B8C(s32, s32, s32, s32);
extern void set_partial_tile_color(s32, s32);
extern void battle_store_name_and_data_of_unit_selected_by_cursor(void);
extern void battle_show_autobattle_feedback(void);

void battle_close_move_help(void) {
    battle_misc_data_t* unit;
    battle_misc_data_t* casting;

    battle_stop_game_flow();
    unit = battle_get_source_unit_misc_data();
    casting = battle_get_casting_unit_misc_data();
    if ((unit->team_flags & 8) != 0) {
        set_at_list_active();
    } else {
        battle_clear_at_list_active();
    }

    if (func_80174B8C(casting->battle_data->misc_unit_id, casting->map_x,
            casting->map_y, casting->map_z)
        > 0) {
        set_partial_tile_color(1, 1);
        g_battle_game_state = BATTLE_GAME_STATE_CLOSE_MOVE_HELP;
        casting->unit_check = 0;
        battle_store_name_and_data_of_unit_selected_by_cursor();
    } else {
        battle_show_autobattle_feedback();
    }
}
