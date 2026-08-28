#include "fft/battle.h"

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void execute_ability(s32 camera_y);
extern s32 g_controller_input_copy_1;
extern s32 g_battle_current_vector_x;
extern s32 g_battle_current_vector_z;
extern s32 g_battle_current_vector_y;
extern s32 g_map_rotation_action;

void battle_handle_pre_attack_animation_state(void) {
    battle_misc_data_t* unit;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    unit = battle_get_source_unit_misc_data();
    if ((unit->animation_countdown == 0 || unit->secondary_animation_state != 0 || unit->unit_check >= 0x3d) && (g_battle_current_vector_x | g_battle_current_vector_z | g_battle_current_vector_y) == 0 && g_map_rotation_action == 0) {
        execute_ability(g_battle_current_vector_y);
    }
}
