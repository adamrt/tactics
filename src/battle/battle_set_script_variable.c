#include "psx/types.h"

extern s32* g_battle_script_variables;

extern void battle_run_script_variable_command(s32 opcode, s32 parameter_1,
    s32 parameter_2,
    s32 parameter_3);

void battle_set_script_variable(s32 variable_id, s32 value) {
    s32 saved_current_variable = *g_battle_script_variables;

    if (variable_id == 0x2c && value > 0x05f5e0ff) {
        value = 0x05f5e0ff;
    }
    battle_run_script_variable_command(0xbe, variable_id, 0, 0);
    battle_run_script_variable_command(0xb0, variable_id, value, 0);
    *g_battle_script_variables = saved_current_variable;
}
