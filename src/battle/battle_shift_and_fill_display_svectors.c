#include "fft/battle.h"

extern void copy_misc_data_screen_xyz_values(battle_svector_t* output, battle_render_unit_t* unit);

void battle_shift_and_fill_display_svectors(battle_render_unit_t* unit) {
    s32 index;

    index = 5;
    do {
        unit->display_svectors[index] = unit->display_svectors[index - 1];
        index--;
    } while (index > 0);
    copy_misc_data_screen_xyz_values(unit->display_svectors, unit);
}
