#include "psx/types.h"

extern s32* g_battle_script_variables;
extern u16 D_80165EE0;

void battle_clear_indexed_script_variable_bit0(void) {
    g_battle_script_variables[D_80165EE0] &= ~1;
}
