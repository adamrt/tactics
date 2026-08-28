#include "psx/types.h"

extern void battle_set_script_variable(s32 variable_id, s32 value);

void battle_advance_date_by_one_year(void) {
    battle_set_script_variable(0x54, 365);
}
