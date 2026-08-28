#include "psx/types.h"

extern s32* g_battle_script_variables;

extern void battle_set_script_variable(s32 variable_id, s32 value);
extern void battle_run_script_variable_command(s32 opcode, s32 parameter_1,
    s32 parameter_2,
    s32 parameter_3);

s32 battle_get_script_variable(s32 variable_id) {
    s32 saved_current_variable = *g_battle_script_variables;

    if (variable_id == 0x22) {
        s32 time_of_day;
        s32 weather;

        time_of_day = battle_get_script_variable(0x24);
        time_of_day &= 1;
        weather = battle_get_script_variable(0x23);
        weather &= 7;
        time_of_day <<= 15;
        weather <<= 12;
        battle_set_script_variable(0x22, time_of_day | weather);
    }
    battle_run_script_variable_command(0xbe, 0, 0, 0);
    battle_run_script_variable_command(0xb1, 0, variable_id, 0);
    {
        s32 value = *g_battle_script_variables;

        *g_battle_script_variables = saved_current_variable;
        return value;
    }
}
