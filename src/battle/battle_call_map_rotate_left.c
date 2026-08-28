#include "psx/types.h"

extern s32 g_map_rotation_action;
extern s32 g_battle_map_rotation_increment;
extern void battle_map_rotate_left(s32);

void battle_call_map_rotate_left(s32 target_angle) {
    g_map_rotation_action = 1;
    g_battle_map_rotation_increment = 1;
    battle_map_rotate_left(target_angle);
}
