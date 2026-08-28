#include "psx/types.h"

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32, s32);
extern s32* battle_get_selected_ability_address(void);
extern void battle_caster_post_effect_messages(void);
extern s32 g_controller_input_copy_1;
extern s32 g_post_action;

void battle_handle_battle_message_display_state(void) {
    s32 selected_ability;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    selected_ability = *battle_get_selected_ability_address();
    if (selected_ability >= 7 && (selected_ability < 9 || selected_ability == 0xff)) {
        g_post_action = 1;
    }
    if (g_post_action != 0) {
        battle_caster_post_effect_messages();
    }
}
