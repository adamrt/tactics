#include "psx/types.h"

extern void battle_restore_current_real_coords(void);

s32 battle_effect_code_script_0a(u16* effect) {
    battle_restore_current_real_coords();
    effect[3] += 2;
    return 1;
}
