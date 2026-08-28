#include "fft/battle.h"

extern s32 g_battle_game_state;
extern s32 g_post_action;
extern void battle_stop_game_flow(void);
extern void* battle_get_casting_unit_misc_data(void);
extern void* get_acting_unit_misc_data(void);
extern void set_at_list_active(void);
extern void store_misc_data_without_control_flag(void*);
extern s32 prepare_action_menu(void*);
extern void battle_rotate_camera_when_unit_tile_not_visible(void*);

void battle_set_next_script_action_menus(void) {
    void* casting_unit;
    void* unit;

    battle_stop_game_flow();
    casting_unit = battle_get_casting_unit_misc_data();
    unit = get_acting_unit_misc_data();
    set_at_list_active();
    store_misc_data_without_control_flag(casting_unit);
    if (prepare_action_menu(unit) == 0) {
        g_battle_game_state = BATTLE_GAME_STATE_OPEN_ACTION_MENUS;
        g_post_action = 0;
        battle_rotate_camera_when_unit_tile_not_visible(casting_unit);
    }
}
