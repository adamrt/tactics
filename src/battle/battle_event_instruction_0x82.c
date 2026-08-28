#include "psx/types.h"

extern s32 battle_get_script_variable(s32);
extern void battle_setup_open_companion_executable(s32);
extern void func_8014CA80(void);
extern void func_801C34B4(void);
extern void func_801C7FE4(void);
extern void func_801C8004(void);
extern s16 D_80165FDA;

void battle_event_instruction_0x82(void) {
    if (battle_get_script_variable(0x1FC) == 0) {
        D_80165FDA = 2;
        battle_setup_open_companion_executable(0xD);
        func_8014CA80();
        func_801C34B4();
        func_801C7FE4();
        func_801C8004();
    }
}
