#include "fft/battle.h"

extern void battle_store_unit_names_and_some_event_block_data(s32 a, s32 b, s32 c);
extern void battle_system_function_setup_routine(s32 a, s32 b, u8 c, s32 d, s32 e);
extern battle_misc_data_t* battle_get_casting_unit_misc_data(void);
extern void set_at_list_active(void);
extern void battle_stop_game_flow(void);
extern s32 g_battle_game_state;
extern s32 g_post_action;

void battle_target_display_start(void) {
    battle_stop_game_flow();
    g_battle_game_state = 0x23;
    battle_store_unit_names_and_some_event_block_data(1, 0xFF, 0xFF);
    battle_system_function_setup_routine(1, 0, battle_get_casting_unit_misc_data()->battle_data->misc_unit_id, 0, 1);
    g_post_action = 0;
    set_at_list_active();
}
