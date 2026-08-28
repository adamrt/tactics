#include "psx/types.h"

extern void battle_stop_game_flow(void);
extern void battle_store_name_and_data_of_unit_selected_by_cursor(void);
extern u8* battle_get_casting_unit_misc_data(void);
extern void battle_highlight_all_units_blue_or_red(u8);
extern s32 g_battle_game_state;

void battle_target_select_mode(void) {
    battle_stop_game_flow();
    g_battle_game_state = 0x20;
    battle_store_name_and_data_of_unit_selected_by_cursor();
    battle_highlight_all_units_blue_or_red(battle_get_casting_unit_misc_data()[0x1B6]);
}
