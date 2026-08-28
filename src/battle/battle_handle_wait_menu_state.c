#include "fft/battle.h"
#include "psx/types.h"

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern s32* battle_get_selected_ability_address(void);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern s32 check_change_of_turn(u8 unit_id);
extern void battle_set_state_after_command(void);
extern void battle_choose_facing_for_wait(void);
extern s32 g_controller_input_copy_1;

void battle_handle_wait_menu_state(void) {
    s32* selected_ability_address;
    s32 selected_ability;
    battle_misc_data_t* source_misc_data;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    selected_ability_address = battle_get_selected_ability_address();
    source_misc_data = battle_get_source_unit_misc_data();
    selected_ability = *selected_ability_address;
    switch (selected_ability) {
    case 8:
    case 0xff:
        if (check_change_of_turn(
                source_misc_data->battle_data->misc_unit_id)
            != 1) {
            battle_set_state_after_command();
            return;
        }
    case 7:
        battle_choose_facing_for_wait();
        return;
    }
}
