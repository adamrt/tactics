#include "psx/types.h"

extern void func_8008b554(s32 expected);

void wldcore_conditional_8008b554_expect_true(void) {
    func_8008b554(1);
}
