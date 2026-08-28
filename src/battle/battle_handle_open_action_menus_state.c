typedef signed int s32;

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern s32* battle_get_selected_ability_address(void);
extern void open_idle_action_menu(void);
extern s32 g_controller_input_copy_1;
extern s32 g_post_action;
extern s32 g_battle_current_vector_x;
extern s32 g_battle_current_vector_z;
extern s32 g_battle_current_vector_y;
extern s32 g_map_rotation_action;

void battle_handle_open_action_menus_state(void) {
    s32 selected_ability;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    selected_ability = *battle_get_selected_ability_address();
    if (selected_ability >= 7 && (selected_ability < 9 || selected_ability == 0xff)) {
        g_post_action = 1;
    }
    if ((g_battle_current_vector_x | g_battle_current_vector_z | g_battle_current_vector_y) == 0 && g_map_rotation_action == 0 && g_post_action != 0) {
        open_idle_action_menu();
    }
}
