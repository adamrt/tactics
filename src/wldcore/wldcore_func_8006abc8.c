#include "psx/types.h"

extern void func_8006AC08(s32* arg0, s32* arg1);
extern void func_8006AC98(s32* arg0, s32* arg1);

void wldcore_func_8006abc8(s32* arg0, s32* arg1) {
    func_8006AC08(arg0, arg1);
    func_8006AC98(arg0, arg1);
}
