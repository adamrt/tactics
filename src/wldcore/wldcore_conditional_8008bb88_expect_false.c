#include "psx/types.h"

extern void func_8008bb88(s32 expected);

void wldcore_conditional_8008bb88_expect_false(void) {
    func_8008bb88(0);
}
