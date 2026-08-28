#include "psx/types.h"

extern void func_800ED104(void);
extern void func_800EDAA8(void);
extern void func_800F6490(s32 arg0);

void world_func_800ed5c4(void) {
    func_800ED104();
    func_800F6490(0xFA);
    func_800EDAA8();
}
