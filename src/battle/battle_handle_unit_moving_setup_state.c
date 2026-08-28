#include "fft/battle.h"
#include "psx/types.h"

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern s32* battle_get_selected_ability_address(void);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void begin_unit_movement(void);
extern void close_move_help(void);
extern s32 g_controller_input_copy_1;

void battle_handle_unit_moving_setup_state(void) {
    s32* selected_ability_address;
    s32 selected_ability;
    battle_misc_data_t* casting_misc_data;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    selected_ability_address = battle_get_selected_ability_address();
    casting_misc_data = battle_get_casting_unit_misc_data();
    selected_ability = *selected_ability_address;
    switch (selected_ability) {
    case 7:
        begin_unit_movement();
        return;
    case 8:
    case 0xff:
        casting_misc_data->movement_path_count = 0;
        close_move_help();
        return;
    }
}
