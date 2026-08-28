#include "psx/types.h"

extern void battle_handle_free_cursor_input(void);
extern s32 func_80044A60(void);
extern void func_8013F520(s32, s32);
extern s32 g_controller_input_raw;
extern s32 g_controller_input_pressed;
extern s32 battle_get_casting_unit_misc_data(void);
extern void battle_move_cursor_to_unit(s32);
extern void battle_set_next_script_action_menus(void);

void battle_main_battletargetdisplaymode_game_state_handler(void) {
    s32 flags;
    battle_handle_free_cursor_input();
    func_8013F520(func_80044A60(), g_controller_input_raw);
    flags = g_controller_input_pressed;
    if ((flags & 0x20) || (flags & 0x40)) {
        battle_move_cursor_to_unit(battle_get_casting_unit_misc_data());
        battle_set_next_script_action_menus();
    }
}
