#include "fft/battle.h"

extern void battle_move_cursor_to_unit(battle_misc_data_t*);
extern void battle_update_display_by_misc_id(s32);
extern void battle_set_state_after_command(void);

void battle_post_command_update_animation_display(battle_misc_data_t* unit) {
    battle_move_cursor_to_unit(unit);
    battle_update_display_by_misc_id(unit->unit_id);
    battle_set_state_after_command();
}
