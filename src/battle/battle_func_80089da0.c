#include "psx/types.h"

extern void func_800898A0(void* unit, s32 allow_height_change);

/* Thin wrapper; the flag gates whether the Y component is also advanced.
   Behaviour of the callee is not yet understood, so the placeholder name
   is kept. */
void battle_func_80089da0(void* unit) {
    func_800898A0(unit, 1);
}
