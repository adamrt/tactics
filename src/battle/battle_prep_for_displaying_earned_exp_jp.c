#include "fft/battle.h"

extern void func_800808B8(battle_misc_data_t* unit, battle_sprite_display_data_t* display, battle_misc_data_t* unit_copy);
extern s32 g_customized_options;

void battle_prep_for_displaying_earned_exp_jp(battle_misc_data_t* unit) {
    battle_sprite_display_data_t* display_0;
    battle_sprite_display_data_t* display_1;
    battle_sprite_display_data_t* display_2;

    if (!(g_customized_options & 0x06000000)) {
        display_0 = unit->numeric_displays[0];
        display_1 = unit->numeric_displays[1];
        display_2 = unit->numeric_displays[2];
        display_2->field_04 = 0x1F;
        display_1->field_04 = 0x1F;
        display_0->field_04 = 0x1F;
        /* display_flags[3] bits 0x02 (Gained Exp) / 0x04 (Gained JP), set
         * through a word RMW of the four flag bytes. */
        if (unit->earned_experience != 0) {
            *(s32*)unit->display_flags |= 0x02000000;
        }
        if (unit->earned_jp != 0) {
            *(s32*)unit->display_flags |= 0x04000000;
        }
        if (unit->numeric_display_active == 0) {
            unit->numeric_display_type = 0;
            func_800808B8(unit, display_0, unit);
        }
    }
}
