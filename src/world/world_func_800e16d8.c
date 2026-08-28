#include "psx/types.h"

extern volatile u16 D_801CD804;
extern volatile u16 D_801CD806;
extern volatile u16 D_801CD808;
extern volatile u16 D_801CD80A;

void world_func_800e16d8(const volatile u16* source) {
    D_801CD804 = source[0];
    D_801CD806 = source[1];
    D_801CD808 = source[2];
    D_801CD80A = source[3];
}
