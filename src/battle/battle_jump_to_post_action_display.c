#include "fft/battle.h"

extern void post_action_display_setup(battle_display_unit_t* unit);
extern void main_pointer_exception_handler(s32 error_code);

s32 battle_jump_to_post_action_display(u16 misc_id) {
    battle_display_unit_t* unit = battle_get_unit_misc_data_by_misc_id(misc_id);
    if (unit != 0) {
        post_action_display_setup(unit);
        return 1;
    }
    main_pointer_exception_handler(0xc);
    return 0;
}
