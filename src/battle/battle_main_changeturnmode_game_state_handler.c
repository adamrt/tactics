#include "psx/types.h"

extern s32 g_post_action;
extern s32 g_battle_current_vector_x;
extern s32 g_battle_current_vector_z;
extern s32 g_battle_current_vector_y;
extern s32 g_map_rotation_action;
extern s32 g_action_type;
extern s32 g_controller_input_raw;
extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 input);
extern s32* battle_get_selected_ability_address(void);
extern void get_acting_unit_misc_data(void);
extern void battle_action_cast_2(void);
extern void func_800711A4(void);
extern void battle_set_next_script_action_menus(void);

void battle_main_changeturnmode_game_state_handler(void) {
    s32 ability;
    s32 type;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_raw);
    ability = *battle_get_selected_ability_address();
    if (ability >= 7) {
        if (ability < 9) {
            g_post_action = 1;
        } else if (ability == 0xFF) {
            g_post_action = 1;
        }
    }
    if (g_post_action != 0) {
        if ((g_battle_current_vector_x | g_battle_current_vector_z | g_battle_current_vector_y) == 0) {
            if (g_map_rotation_action == 0) {
                get_acting_unit_misc_data();
                type = g_action_type;
                if (type == 0x200) {
                    battle_action_cast_2();
                    return;
                }
                if ((type == 0x300) || (type == 0x500)) {
                    func_800711A4();
                    return;
                }
                battle_set_next_script_action_menus();
            }
        }
    }
}
