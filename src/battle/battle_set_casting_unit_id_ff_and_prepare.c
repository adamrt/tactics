#include "psx/types.h"

extern void battle_set_casting_unit_id_ff(void);
extern void system_function_setup(s32, s32, s32, s32, s32);

void battle_set_casting_unit_id_ff_and_prepare(void) {
    battle_set_casting_unit_id_ff();
    system_function_setup(8, 0, 0xff, 0, 1);
}
