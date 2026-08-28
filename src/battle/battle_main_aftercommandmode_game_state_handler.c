#include "fft/battle.h"

extern void battle_handle_free_cursor_input(void);
extern s32 func_80044A60(void);
extern void func_8013F520(s32, s32);
extern s32 g_controller_input_raw;
extern s32* battle_get_selected_ability_address(void);
extern battle_misc_data_t* battle_get_source_unit_misc_data(void);
extern void battle_set_state_jp_xp_gain(void);
extern s32 g_post_action;

void battle_main_aftercommandmode_game_state_handler(void) {
    s32* ability_addr;
    s32 ability;
    battle_misc_data_t* unit;

    battle_handle_free_cursor_input();
    func_8013F520(func_80044A60(), g_controller_input_raw);
    ability_addr = battle_get_selected_ability_address();
    unit = battle_get_source_unit_misc_data();
    ability = *ability_addr;
    if ((ability >= 7) && ((ability < 9) || (ability == 0xFF))) {
        g_post_action = 1;
    }
    if ((g_post_action != 0) && (unit->numeric_display_active == 0)) {
        battle_set_state_jp_xp_gain();
    }
}
