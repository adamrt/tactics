#include "psx/types.h"

extern void battle_copy_current_real_coords(void);

s32 battle_effect_code_script_09(u16* effect) {
    battle_copy_current_real_coords();
    effect[3] += 2;
    return 1;
}
