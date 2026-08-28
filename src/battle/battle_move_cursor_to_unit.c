#include "fft/battle.h"

extern s32 g_battle_cursor_x;
extern s32 g_battle_cursor_z;
extern s32 g_battle_cursor_y;

void battle_move_cursor_to_unit(battle_display_unit_t* unit) {
    if (unit != 0) {
        g_battle_cursor_x = unit->map_x;
        g_battle_cursor_y = unit->map_y;
        g_battle_cursor_z = unit->map_z;
    }
}
