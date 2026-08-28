#include "fft/battle.h"

extern s32 battle_is_menu_still_building(void);
extern void battle_start_game_flow(void);
extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern s32 g_controller_input_copy_1;
extern s32 g_help_menu_opening;
extern s32 g_battle_game_state;

void battle_handle_ability_preview_help_state(void) {
    if (battle_is_menu_still_building() != 2) {
        g_help_menu_opening = 0;
        battle_start_game_flow();
        g_battle_game_state = BATTLE_GAME_STATE_ABILITY_PREVIEW_HANDLING;
    }
    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
}
