#include "fft/battle.h"
#include "psx/types.h"

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern s32* battle_get_selected_ability_address(void);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void copy_rider_data_to_mount(battle_misc_data_t* source,
    battle_misc_data_t* casting);
extern void undo_mount(battle_misc_data_t* casting);
extern void battle_update_unit_palettes(void);
extern void close_move_help(void);
extern s32 g_controller_input_copy_1;

void battle_handle_move_confirm_menu_state(void) {
    s32* selected_ability_address;
    s32 selected_ability;
    battle_misc_data_t* source_misc_data;
    battle_misc_data_t* casting_misc_data;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    selected_ability_address = battle_get_selected_ability_address();
    source_misc_data = battle_get_source_unit_misc_data();
    casting_misc_data = battle_get_casting_unit_misc_data();
    selected_ability = *selected_ability_address;
    switch (selected_ability) {
    case 8:
    case 0xff:
        if (casting_misc_data->movement_flags & 8) {
        case 7:
            copy_rider_data_to_mount(source_misc_data, casting_misc_data);
            return;
        }
        undo_mount(casting_misc_data);
        battle_update_unit_palettes();
        close_move_help();
        return;
    }
}
