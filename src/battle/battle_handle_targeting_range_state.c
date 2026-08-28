#include "fft/battle.h"

extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern void move_cursor_based_on_input(void);
extern void handle_map_rotation_input(void);
extern void battle_call_map_zoom(void);
extern void battle_call_map_tilt(void);
extern void set_partial_tile_color(s32, s32);
extern void battle_open_active_unit_idle_action_menu(void);
extern u8* battle_get_tile_data_pointer(s32, s32, s32);
extern void select_target_tile(void);
extern void target_out_of_range(void);
extern void free_cursor_selection(battle_misc_data_t*, battle_misc_data_t*);
extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(u8);
extern void battle_set_next_script_action_menus(void);
extern s32 g_controller_input_copy_1;
extern s32 g_controller_input;
extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_z;
extern s32 g_battle_cursor_y;

void battle_handle_targeting_range_state(void) {
    u16 frame_data;
    battle_misc_data_t* unit;
    battle_misc_data_t* target;

    unit = battle_get_source_unit_misc_data();
    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    if ((unit->team_flags & 8) != 0) {
        move_cursor_based_on_input();
        handle_map_rotation_input();
        battle_call_map_zoom();
        battle_call_map_tilt();
        if ((g_controller_input & 0x40) != 0) {
            set_partial_tile_color(0, 2);
            battle_open_active_unit_idle_action_menu();
            return;
        }
        if ((g_controller_input & 0x20) != 0) {
            if ((battle_get_tile_data_pointer(g_battle_cursor_x, g_battle_cursor_y,
                     g_battle_cursor_z)[5]
                    & 0x40)
                != 0) {
                select_target_tile();
                return;
            }
            target_out_of_range();
        }
    } else {
        /* 0x166/0x167 (target type / target battle id) share the facing_hint
         * word with the WAIT_DIRECTION state; the header keeps the word. */
        switch (*((u8*)unit + 0x166)) {
        case 5:
            free_cursor_selection(unit, 0);
            frame_data = unit->unit_check++;
            if (frame_data >= 0x1f) {
                battle_get_tile_data_pointer(unit->target_panel_x,
                    unit->target_panel_y,
                    unit->target_map_level);
                select_target_tile();
            }
            return;
        case 6:
            target = battle_get_unit_misc_data_by_battle_id(*((u8*)unit + 0x167));
            if (target != 0) {
                free_cursor_selection(unit, target);
                frame_data = unit->unit_check++;
                if (frame_data >= 0x1f) {
                    battle_get_tile_data_pointer(target->map_x, target->map_y,
                        target->map_z);
                    select_target_tile();
                }
            } else {
                battle_set_next_script_action_menus();
            }
            break;
        }
    }
}
