#include "psx/types.h"

extern s32 battle_deep_dungeon_crystal_check_and_map_state_preparation(void);
extern s32 g_battle_game_state;
extern s32 g_animation_speed;

s32 battle_refresh_deep_dungeon(void) {
    if (battle_deep_dungeon_crystal_check_and_map_state_preparation()) {
        g_battle_game_state = 0x31;
        g_animation_speed = 1;
        return 1;
    }
    return 0;
}
