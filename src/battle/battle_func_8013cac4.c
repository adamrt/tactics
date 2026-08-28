#include "psx/types.h"

extern u8 D_8014E5D4[];
extern void func_8013CA70(u8* arg0);
extern void func_8014A51C(void);

void battle_func_8013cac4(void) {
    func_8013CA70(D_8014E5D4);
    func_8014A51C();
}
