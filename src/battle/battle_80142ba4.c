#include "psx/types.h"

extern u16 g_scenario_event_finish_operations[];
extern s32 D_80173C74;

u32 battle_80142ba4(void) {
    return (u32)(g_scenario_event_finish_operations[D_80173C74] & 0xF300) >> 8;
}
