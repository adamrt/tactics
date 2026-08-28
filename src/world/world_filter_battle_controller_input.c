#include "psx/types.h"

extern s32 D_8019A218;
extern void func_800F64E4(void);

void world_filter_battle_controller_input(s32* src) {
    D_8019A218 = *src;
    func_800F64E4();
}
