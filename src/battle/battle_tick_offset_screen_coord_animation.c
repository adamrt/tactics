#include "fft/battle.h"

extern battle_real_coords_t g_battle_offset_screen_coords;
extern battle_real_coords_t g_battle_offset_screen_coords_fixed;
extern battle_real_coords_t g_battle_real_coord_delta;
extern u16 g_battle_offset_screen_coord_countdown;

void battle_tick_offset_screen_coord_animation(void) {
    s32 fixed_x;
    s32 fixed_z;
    s32 fixed_y;

    if (g_battle_offset_screen_coord_countdown != 0) {
        fixed_x = g_battle_offset_screen_coords_fixed.x + g_battle_real_coord_delta.x;
        g_battle_offset_screen_coords_fixed.x = fixed_x;
        fixed_z = g_battle_offset_screen_coords_fixed.z + g_battle_real_coord_delta.z;
        fixed_y = g_battle_offset_screen_coords_fixed.y + g_battle_real_coord_delta.y;
        g_battle_offset_screen_coords_fixed.z = fixed_z;
        g_battle_offset_screen_coords_fixed.y = fixed_y;
        g_battle_offset_screen_coords.x = fixed_x / 0x1000;
        g_battle_offset_screen_coords.z = fixed_z / 0x1000;
        g_battle_offset_screen_coords.y = fixed_y / 0x1000;
        g_battle_offset_screen_coord_countdown--;
    }
}
