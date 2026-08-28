#include "psx/types.h"

extern s32 battle_get_script_variable(s32 slot);

s32 battle_check_if_tutorial_event_slot(void) {
    return (u32)(battle_get_script_variable(0x27) - 0x19A) < 0x10U;
}
