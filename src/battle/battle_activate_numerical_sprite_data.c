#include "fft/battle.h"

extern void func_800808B8(battle_misc_data_t*);

void battle_activate_numerical_sprite_data(battle_misc_data_t* unit, s32 mode) {
    battle_sprite_display_data_t* display_0 = unit->numeric_displays[0];
    battle_sprite_display_data_t* display_1 = unit->numeric_displays[1];
    battle_sprite_display_data_t* display_2 = unit->numeric_displays[2];

    display_2->field_04 = 0x1F;
    display_1->field_04 = 0x1F;
    display_0->field_04 = 0x1F;
    /* display_flags[3] bits 0x08 / 0x10 / 0x20 ("No Target", "Silenced",
     * "No MP"), set through a word RMW of the four flag bytes. */
    switch (mode) {
    case 1:
        *(u32*)unit->display_flags |= 0x08000000;
        break;
    case 2:
        *(u32*)unit->display_flags |= 0x10000000;
        break;
    case 3:
        *(u32*)unit->display_flags |= 0x20000000;
        break;
    }
    if (unit->numeric_display_active == 0) {
        unit->numeric_display_type = 0;
        func_800808B8(unit);
    }
}
