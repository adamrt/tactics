typedef signed int s32;

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern s32* battle_get_selected_ability_address(void);
extern void close_move_help(void);
extern s32 g_controller_input_copy_1;

void battle_handle_illegal_move_menu_state(void) {
    s32 selected_ability;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    selected_ability = *battle_get_selected_ability_address();
    if (selected_ability >= 7 && (selected_ability < 9 || selected_ability == 0xff)) {
        close_move_help();
    }
}
