#include "psx/types.h"

extern s16 battle_load_halfword(s32);
extern s32 battle_get_script_variable(s32);
extern void func_8014CA80(void);

/* WaitValue event instruction: spin until script variable p[0] >= p[2]. */
void battle_wait_value_event_instruction(s32 arg0) {
    s32 a;
    s32 b;

    a = battle_load_halfword(arg0);
    b = battle_load_halfword(arg0 + 2);
    while (battle_get_script_variable(a) < b) {
        func_8014CA80();
    }
}
