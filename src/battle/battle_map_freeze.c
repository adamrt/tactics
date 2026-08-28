#include "psx/types.h"

extern void dispatch_map_data_command(s32 command, s32 arg1, s32 arg2,
    s32 arg3);

void battle_map_freeze(void) {
    dispatch_map_data_command(0x71, 0, 0, 0);
}
