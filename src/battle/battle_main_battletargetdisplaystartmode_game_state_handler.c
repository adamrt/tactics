#include "psx/types.h"

extern s32 g_post_action;
extern s32 g_battle_current_vector_x;
extern s32 g_battle_current_vector_y;
extern s32 g_battle_current_vector_z;
extern s32 g_map_rotation_action;
extern s32 g_controller_input_raw;

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32, s32);
extern s32* battle_get_selected_ability_address(void);
extern void battle_target_display(void);

void battle_main_battletargetdisplaystartmode_game_state_handler(void) {
    s32 id;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_raw);
    id = *battle_get_selected_ability_address();
    if ((id >= 7) && ((id < 9) || (id == 0xFF))) {
        g_post_action = 1;
    }
    if ((g_battle_current_vector_x | g_battle_current_vector_z | g_battle_current_vector_y) == 0) {
        if (g_map_rotation_action == 0) {
            if (g_post_action != 0) {
                battle_target_display();
            }
        }
    }
}
