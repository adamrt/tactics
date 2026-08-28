typedef signed int s32;

extern void battle_open_mini_menu(void);
extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern s32 g_controller_input;
extern s32 g_controller_input_copy_1;

void battle_handle_active_turn_state(void) {
    s32 controller_input;

    controller_input = g_controller_input;
    if ((controller_input & 0x20) || (controller_input & 0x40)) {
        battle_open_mini_menu();
    }
    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
}
