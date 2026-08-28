#include "psx/types.h"

extern void battle_set_camera_zoom(const s32* args);

s32 battle_effect_code_script_0e(u16* effect) {
    s32 args[3];
    args[0] = *(s16*)((s32) * (s16*)(effect + 3) + *(s32*)(effect + 4) + 2);
    args[1] = *(s16*)((s32) * (s16*)(effect + 3) + *(s32*)(effect + 4) + 4);
    args[2] = *(s16*)((s32) * (s16*)(effect + 3) + *(s32*)(effect + 4) + 6);
    battle_set_camera_zoom(args);
    effect[3] += 8;
    return 1;
}
