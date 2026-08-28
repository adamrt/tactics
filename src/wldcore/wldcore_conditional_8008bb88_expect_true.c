#include "psx/types.h"

extern void func_8008bb88(s32 expected);

void wldcore_conditional_8008bb88_expect_true(void) {
    func_8008bb88(1);
}
