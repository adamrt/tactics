#include "psx/types.h"

extern void battle_set_camera_rotation(const u16* rotation);

s32 battle_effect_code_script_0b(u16* effect) {
    u16 args[3];
    args[0] = *(u16*)((s32) * (s16*)(effect + 3) + *(s32*)(effect + 4) + 2);
    args[1] = *(u16*)((s32) * (s16*)(effect + 3) + *(s32*)(effect + 4) + 4);
    args[2] = *(u16*)((s32) * (s16*)(effect + 3) + *(s32*)(effect + 4) + 6);
    battle_set_camera_rotation(args);
    effect[3] += 8;
    return 1;
}
