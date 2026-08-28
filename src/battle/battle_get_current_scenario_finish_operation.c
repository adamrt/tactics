#include "psx/types.h"

extern s16 D_80173cb0;
extern u16 g_scenario_event_finish_operations[];
extern s32 battle_get_script_variable(s32 id);

u16 battle_get_current_scenario_finish_operation(void) {
    if (D_80173cb0 == 0) {
        return 0;
    }
    return g_scenario_event_finish_operations[battle_get_script_variable(0x27)];
}
