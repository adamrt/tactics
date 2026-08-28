#include "fft/battle.h"

extern s32 g_animation_speed;
extern s32 g_battle_game_state;
extern s32 g_help_menu_opening;
extern void battle_stop_game_flow(void);
extern void store_name_and_unit_data_under_cursor(void);
extern void set_at_list_active(void);
extern void* get_acting_unit_misc_data(void);
extern void store_misc_data_without_control_flag(void*);

void battle_set_game_state_free_cursor(void) {
    void* unit;

    g_animation_speed = 1;
    battle_stop_game_flow();
    g_battle_game_state = BATTLE_GAME_STATE_FREE_CURSOR;
    g_help_menu_opening = 0;
    store_name_and_unit_data_under_cursor();
    set_at_list_active();
    unit = get_acting_unit_misc_data();
    if (unit != 0) {
        store_misc_data_without_control_flag(unit);
    }
}
