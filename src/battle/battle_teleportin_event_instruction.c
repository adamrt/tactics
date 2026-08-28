#include "psx/types.h"

extern s32 func_80133158(void);
extern void func_8014CEB4(s32 arg0);
extern void battle_teleport_effect_callback(void);

void battle_teleportin_event_instruction(void) {
    s32 temp_v0;

    temp_v0 = func_80133158();
    if (temp_v0 != 0x7D0) {
        *(void (**)(void))0x80173CA8 = &battle_teleport_effect_callback;
        func_8014CEB4(temp_v0);
    }
}
