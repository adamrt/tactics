#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void main_pointer_exception_handler(s32 exception_id);
extern void battle_remove_misc_unit(battle_misc_data_t* unit);

s32 battle_remove_misc_unit_by_id(u32 misc_id) {
    battle_misc_data_t* unit;

    unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xFFFF);
    if (unit != 0) {
        battle_remove_misc_unit(unit);
        return 1;
    }
    main_pointer_exception_handler(0xC);
    return 0;
}
