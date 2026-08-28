#include "psx/types.h"

extern void battle_set_current_real_coords(s32* xyz);

s32 battle_effect_code_script_08(u8* effect) {
    s32 v[3];
    v[0] = ((s16*)(*(s16*)(effect + 6) + *(s32*)(effect + 8)))[1] << 12;
    v[1] = ((s16*)(*(s16*)(effect + 6) + *(s32*)(effect + 8)))[2] << 12;
    v[2] = ((s16*)(*(s16*)(effect + 6) + *(s32*)(effect + 8)))[3] << 12;
    battle_set_current_real_coords(v);
    *(s16*)(effect + 6) += 8;
    return 1;
}
