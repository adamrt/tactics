typedef signed int s32;

extern s32 battle_is_menu_still_building(void);
extern void battle_open_mini_menu_help();
extern void battle_set_game_state_free_cursor();
extern void select_next_acting_unit(s32 at_list_index);
extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern s32 g_controller_input;
extern s32 g_controller_input_copy_1;
extern s32 g_shifted_controller_flags;
extern s32 g_battle_controller_input;

void battle_handle_mini_menu_state(void) {
    s32 menu_result;

    menu_result = battle_is_menu_still_building();
    if (g_controller_input & 0x100) {
        battle_open_mini_menu_help();
    } else if (menu_result == 0) {
        g_battle_controller_input = g_shifted_controller_flags & 7;
        battle_set_game_state_free_cursor();
    } else if (menu_result >= 0x64) {
        select_next_acting_unit(menu_result - 0x64);
    }
    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
}
