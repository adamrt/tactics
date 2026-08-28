#include "psx/types.h"

extern void battle_stop_game_flow(void);
extern s32 battle_get_source_unit_misc_data(void);
extern s32 func_80070A38(s32);
extern void battle_rotate_camera_when_unit_tile_not_visible(s32);
extern s32 g_battle_game_state;
extern s32 g_post_action;

void battle_action_cast_2(void) {
    s32 unit;

    battle_stop_game_flow();
    g_battle_game_state = 0x1D;
    g_post_action = 0;
    unit = battle_get_source_unit_misc_data();
    if (func_80070A38(unit) == 0) {
        g_battle_game_state = 0x1D;
        battle_rotate_camera_when_unit_tile_not_visible(unit);
    }
}
