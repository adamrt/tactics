#include "psx/types.h"

extern s32 D_800F668C;
extern s32 D_80122000;
extern s32 D_800F7A54;
extern s16 D_800F5B60;

void battle_func_800f5a2c(s32 id, s32 value) {
    if (id == 0x96) {
        D_800F668C = 0x95;
        D_80122000 = value;
        D_800F7A54 = 0;
        D_800F5B60 = 0x96;
    }
}
