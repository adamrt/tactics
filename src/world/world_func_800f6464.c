#include "psx/types.h"

extern u16 g_scenario_event_finish_operations[];
extern s32 D_801A6690;

u32 world_func_800f6464(void) {
    return (u32)(g_scenario_event_finish_operations[D_801A6690] & 0xF300) >> 8;
}
