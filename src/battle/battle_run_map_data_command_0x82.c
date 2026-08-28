#include "psx/types.h"

extern void dispatch_map_data_command(s32, s32, s32, s32);

void battle_run_map_data_command_0x82(s32 value) {
    dispatch_map_data_command(0x82, value, 1, 1);
}
