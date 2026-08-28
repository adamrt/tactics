#include "psx/types.h"

extern void func_80089BA0(void* unit, s32 allow_height_change);

void battle_func_80089e00(void* unit) {
    func_80089BA0(unit, 0);
}
