#include "fft/battle.h"

extern s32 battle_calculate_screen_z_from_misc_screen_data(battle_misc_data_t* unit);
extern void battle_set_real_coords_from_screen_coords(battle_misc_data_t* unit);

void battle_update_float_and_jump_height(battle_misc_data_t* unit) {
    u32 grounded;
    /* Pin: without it GCC loads movement.word into $v1 and the 0x10000000
     * constant into $v0 in the floating arm (register swap only; every
     * per-block-local variant tried keeps the swap). */
    register u32 movement __asm__("$2");

    if (unit->status_flags_5_6 & 0x20) {
        movement = unit->movement.word;
        movement = movement | 0x10000000;
    } else {
        grounded = unit->movement.word;
        movement = grounded & 0xefffffff;
    }
    unit->movement.word = movement;

    /* Reusing `movement` for the reload keeps the store above it; a fresh
     * local lets GCC sink the store into the branch delay slot. */
    movement = unit->status_flags_5_6;
    if ((movement & 0x240) == 0 && (unit->statuses_to_remove_5_6 & 0x40) == 0) {
        unit->screen_z = battle_calculate_screen_z_from_misc_screen_data(unit);
        battle_set_real_coords_from_screen_coords(unit);
    }
}
