#include "psx/types.h"

extern s32* g_world_event_words;

extern void world_run_event_instruction(s32 opcode, s32 parameter_1, s32 parameter_2, s32 parameter_3);

void world_set_script_variable(s32 variable_id, s32 value) {
    s32 saved_current_variable = *g_world_event_words;

    if (variable_id == 0x2c && value > 0x05f5e0ff) {
        value = 0x05f5e0ff;
    }
    world_run_event_instruction(0xbe, variable_id, 0, 0);
    world_run_event_instruction(0xb0, variable_id, value, 0);
    *g_world_event_words = saved_current_variable;
}
