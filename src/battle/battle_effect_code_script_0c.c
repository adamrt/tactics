#include "psx/types.h"

extern void battle_copy_camera_rotation(void);

s32 battle_effect_code_script_0c(u16* effect) {
    battle_copy_camera_rotation();
    effect[3] += 2;
    return 1;
}
