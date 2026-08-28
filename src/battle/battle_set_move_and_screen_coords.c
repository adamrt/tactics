#include "fft/battle.h"

extern s16 calculate_screen_z_from_misc_screen_data(battle_misc_data_t* unit);
extern void battle_set_real_coords_from_screen_coords(battle_misc_data_t* unit);

void battle_set_move_and_screen_coords(battle_misc_data_t* unit) {
    unit->movement.bytes.destination_x = unit->map_x;
    unit->movement.bytes.destination_y = unit->map_y;
    unit->movement.bytes.destination_z = unit->map_z;
    unit->screen_x = unit->map_x * 28 + 14;
    unit->screen_y = unit->map_y * 28 + 14;
    unit->screen_z = calculate_screen_z_from_misc_screen_data(unit);
    battle_set_real_coords_from_screen_coords(unit);
}
