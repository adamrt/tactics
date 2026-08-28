#include "psx/types.h"

extern s32 func_80133158(void);
extern void func_8014CA80(void);
extern s32 battle_unit_moving_check_by_misc_id(s32);

void battle_waitwalk_event_instruction(void) {
    s32 misc_id = func_80133158();
    if (misc_id != 0x7D0) {
        do {
            func_8014CA80();
        } while (battle_unit_moving_check_by_misc_id(misc_id) != 0);
    }
}
