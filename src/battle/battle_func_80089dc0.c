#include "psx/types.h"

extern void func_80089BA0(void* unit, s32 allow_height_change);

/* Thin wrapper; placeholder name kept, see battle_func_80089da0. */
void battle_func_80089dc0(void* unit) {
    func_80089BA0(unit, 1);
}
