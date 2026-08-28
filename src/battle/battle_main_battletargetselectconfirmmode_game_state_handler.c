#include "fft/battle.h"
#include "psx/types.h"

extern void battle_handle_free_cursor_input(void);
extern u32* func_80044A60(void);
extern void func_8013F520(u32* ot, s32 input);
extern s32* battle_get_selected_ability_address(void);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern battle_misc_data_t* battle_get_misc_data_at_map_coords_2(s32 x, s32 y, s32 z);
extern void battle_store_main_target_id_auto_battle(s32 a, s32 b);
extern void battle_move_cursor_to_unit(battle_misc_data_t* unit);
extern void battle_set_next_script_action_menus(void);
extern void battle_target_select_mode(void);

extern s32 g_controller_input_copy_1;
extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_y;
extern s32 g_battle_cursor_z;

void battle_main_battletargetselectconfirmmode_game_state_handler(void) {
    battle_misc_data_t* caster;
    battle_misc_data_t* target;

    battle_handle_free_cursor_input();
    func_8013F520(func_80044A60(), g_controller_input_copy_1);
    switch (*battle_get_selected_ability_address()) {
    case 7:
        caster = battle_get_casting_unit_misc_data();
        target = battle_get_misc_data_at_map_coords_2(g_battle_cursor_x,
            g_battle_cursor_y,
            g_battle_cursor_z);
        battle_store_main_target_id_auto_battle(target->battle_data->misc_unit_id,
            caster->battle_data->misc_unit_id);
        battle_move_cursor_to_unit(caster);
        battle_set_next_script_action_menus();
        break;
    case 8:
    case 0xFF:
        battle_target_select_mode();
        break;
    }
}
