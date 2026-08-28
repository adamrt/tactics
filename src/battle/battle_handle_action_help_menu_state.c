typedef unsigned char u8;
typedef signed int s32;

typedef struct BattleMiscDataHeader {
    u8 _pad00[4];
    u8 entd_id;
} BattleMiscDataHeader;

extern s32 battle_is_menu_still_building(void);
extern BattleMiscDataHeader* battle_get_casting_unit_misc_data(void);
extern void battle_open_active_unit_idle_action_menu(void);
extern void open_non_active_unit_action_menu(void);
extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern s32 g_controller_input_copy_1;
extern s32 g_help_menu_opening;
extern s32 g_casting_unit_misc_id;

void battle_handle_action_help_menu_state(void) {
    BattleMiscDataHeader* misc_data;

    if (battle_is_menu_still_building() != 2) {
        g_help_menu_opening = 0;
        misc_data = battle_get_casting_unit_misc_data();
        if (misc_data != 0) {
            if (misc_data->entd_id == g_casting_unit_misc_id) {
                battle_open_active_unit_idle_action_menu();
            } else {
                open_non_active_unit_action_menu();
            }
        }
    }
    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
}
