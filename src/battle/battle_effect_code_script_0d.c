#include "psx/types.h"

extern void battle_restore_camera_rotation(void);

s32 battle_effect_code_script_0d(u16* effect) {
    battle_restore_camera_rotation();
    effect[3] += 2;
    return 1;
}
