typedef signed int s32;

extern void set_partial_tile_color(s32 color, s32 mode);
extern void main_play_sound(s32 sound_id);
extern void battle_set_game_state_free_cursor(void);
extern void handle_map_rotation_input(void);
extern void battle_call_map_zoom(void);
extern void battle_call_map_tilt(void);
extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern s32 g_controller_input;
extern s32 g_controller_input_copy_1;
extern s32 g_battle_controller_input;
extern s32 g_controller_input_copy_12;

void battle_handle_display_move_area_state(void) {
    if (g_controller_input & 0x40) {
        set_partial_tile_color(0, 1);
        g_battle_controller_input = g_controller_input_copy_12;
        main_play_sound(2);
        battle_set_game_state_free_cursor();
    }
    handle_map_rotation_input();
    battle_call_map_zoom();
    battle_call_map_tilt();
    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
}
