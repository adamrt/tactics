#include "psx/types.h"

extern s32* g_battle_script_variables;

void battle_event_instructions_a0_a5(s32 opcode) {
    /* Pin: each block begins `lui v0,0x8016`; with the pointer in $v0 the
     * five `bne` delay slots fill with the next `li v0,0xNN` (264 bytes).
     * Unpinned GCC uses $a0 and emits nops instead (280 bytes; cookbook). */
    register s32* vars __asm__("$2");

    if (opcode == 0xA0) {
        vars = g_battle_script_variables;
        vars[0] = vars[0] <= vars[1];
        return;
    }
    if (opcode == 0xA1) {
        vars = g_battle_script_variables;
        vars[0] = vars[0] >= vars[1];
        return;
    }
    if (opcode == 0xA2) {
        vars = g_battle_script_variables;
        vars[0] = vars[0] == vars[1];
        return;
    }
    if (opcode == 0xA3) {
        vars = g_battle_script_variables;
        vars[0] = vars[0] != vars[1];
        return;
    }
    if (opcode == 0xA4) {
        vars = g_battle_script_variables;
        vars[0] = vars[0] < vars[1];
        return;
    }
    if (opcode == 0xA5) {
        vars = g_battle_script_variables;
        vars[0] = vars[0] > vars[1];
        return;
    }
}
