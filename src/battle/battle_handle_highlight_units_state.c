typedef signed int s32;

extern void battle_set_game_state_free_cursor(void);
extern void battle_update_unit_palettes(void);
extern void handle_map_rotation_input(void);
extern void battle_call_map_zoom(void);
extern void battle_call_map_tilt(void);
extern void battle_handle_free_cursor_input(void);
extern s32 g_controller_input_copy_6;
extern s32 g_battle_controller_input;
extern s32 g_controller_input_copy_12;

void battle_handle_highlight_units_state(void) {
    if (g_controller_input_copy_6 & 0x80) {
        g_battle_controller_input = g_controller_input_copy_12;
        battle_set_game_state_free_cursor();
        battle_update_unit_palettes();
    }
    handle_map_rotation_input();
    battle_call_map_zoom();
    battle_call_map_tilt();
    battle_handle_free_cursor_input();
}
