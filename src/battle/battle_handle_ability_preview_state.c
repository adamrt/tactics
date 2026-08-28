#include "fft/battle.h"

extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void handle_map_rotation_input(void);
extern void battle_call_map_zoom(void);
extern void battle_call_map_tilt(void);
extern void set_partial_tile_color(s32, s32);
extern void battle_update_unit_palettes(void);
extern void battle_open_active_unit_idle_action_menu(void);
extern void battle_set_target_boxes_red(void);
extern void confirm_action(void);
extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern s32 g_controller_input;
extern s32 g_controller_input_copy_12;
extern s32 g_controller_input_copy_1;
extern s32 g_battle_controller_input;

void battle_handle_ability_preview_state(void) {
    u16 frame_data;
    battle_misc_data_t* unit;

    unit = battle_get_source_unit_misc_data();
    if ((unit->team_flags & 8) != 0) {
        handle_map_rotation_input();
        battle_call_map_zoom();
        battle_call_map_tilt();
        if ((g_controller_input & 0x20) == 0) {
            if ((g_controller_input & 0x40) != 0) {
                g_battle_controller_input = g_controller_input_copy_12;
                set_partial_tile_color(8, 3);
                if (unit->ability_preview_phase == 2) {
                    set_partial_tile_color(0, 3);
                    battle_update_unit_palettes();
                    battle_open_active_unit_idle_action_menu();
                } else {
                    set_partial_tile_color(0, 3);
                    battle_update_unit_palettes();
                    battle_set_target_boxes_red();
                }
            }
        } else {
            goto confirm;
        }
    } else {
        frame_data = unit->unit_check;
        unit->unit_check = frame_data + 1;
        if (frame_data >= 0x1f) {
        confirm:
            g_battle_controller_input = g_controller_input_copy_12;
            battle_update_unit_palettes();
            confirm_action();
        }
    }
    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
}
