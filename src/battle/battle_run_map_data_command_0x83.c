#include "psx/types.h"

extern void dispatch_map_data_command(s32, s32, s32, s32);

s32 battle_run_map_data_command_0x83(s32 value_a, s32 value_b) {
    dispatch_map_data_command(0x83, value_a, value_b, 1);
    return 1;
}
