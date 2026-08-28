#include "psx/types.h"

extern s16 D_801c000c;
extern s16 D_801c000e;
extern s16 D_801c0010;
extern s16 D_801c0012;

void world_func_8010a480(s16 a, s16 b, s16 c, s16 d) {
    D_801c000c = a;
    D_801c000e = b;
    D_801c0010 = c;
    D_801c0012 = d;
}
