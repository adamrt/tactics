#include "fft/battle.h"

extern void battle_set_message_duration_frames(s32);
extern void system_function_setup(s32, s32, u8, u8, s32);
extern void battle_set_level_up_animation(battle_misc_data_t*);
extern void battle_move_cursor_to_unit(battle_misc_data_t*);
extern void battle_set_secondary_effect_level_up(battle_misc_data_t*);
extern void main_play_tune(s32);

s32 battle_level_up_animation_and_report(battle_misc_data_t* misc) {
    if (misc->level_for_display != 0) {
        u8 battle_id;
        battle_set_message_duration_frames(0xB4);
        battle_id = misc->battle_data->misc_unit_id;
        system_function_setup(0xA, 0x183F, battle_id, battle_id, 1);
        battle_set_level_up_animation(misc);
        battle_move_cursor_to_unit(misc);
        battle_set_secondary_effect_level_up(misc);
        main_play_tune(1);
        return 1;
    }
    return 0;
}

/* padding */
