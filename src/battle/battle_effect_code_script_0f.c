#include "psx/types.h"

extern void battle_copy_camera_zoom(void);

s32 battle_effect_code_script_0f(u16* effect) {
    battle_copy_camera_zoom();
    effect[3] += 2;
    return 1;
}
