#include "fft/battle.h"

extern void battle_handle_free_cursor_input(void);
extern s32 main_get_otag(void);
extern void render_menu_selection_data(s32 otag, s32 controller_input);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void battle_set_only_action_taken(u8 unit_id);
extern void battle_post_command_update_animation_display(battle_misc_data_t* unit);
extern void action_phase_control(void);
extern s32 g_controller_input_copy_1;
extern s32 g_battle_action_phase;

void battle_handle_commence_attack_phase_state(void) {
    battle_misc_data_t* unit;

    battle_handle_free_cursor_input();
    render_menu_selection_data(main_get_otag(), g_controller_input_copy_1);
    unit = battle_get_source_unit_misc_data();
    if (unit->attack_phase_state == 3) {
        if (unit->animation_countdown == 0) {
            battle_set_only_action_taken(unit->battle_data->misc_unit_id);
            battle_post_command_update_animation_display(unit);
        }
    } else {
        g_battle_action_phase = 0;
        action_phase_control();
    }
}
