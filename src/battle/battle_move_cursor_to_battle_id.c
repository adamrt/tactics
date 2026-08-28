#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_battle_id(u32 battle_id);
extern void battle_move_cursor_to_unit(battle_display_unit_t* unit);

s32 battle_move_cursor_to_battle_id(u32 battle_id) {
    battle_misc_data_t* unit;

    unit = battle_get_unit_misc_data_by_battle_id(battle_id & 0xFFFF);
    if (unit != 0) {
        battle_move_cursor_to_unit((battle_display_unit_t*)unit);
        return 1;
    }
    return 0;
}
