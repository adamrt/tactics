#include "psx/types.h"

extern void func_8008bc58(s32 expected);

void wldcore_conditional_8008bc58_expect_true(void) {
    func_8008bc58(1);
}
