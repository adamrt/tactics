#include "psx/types.h"

extern s16 D_801EB20C[];
extern s16 D_801CF87E;
extern s16 D_801CF892;
extern s16 func_8002398C(s32, s32, s32, s32);

void bunit_init_rhombus_cursor_tpages(void) {
    s16 term = -1;
    s32 v = 0x1C;
    do {
        *(s16*)((char*)D_801EB20C + v) = term;
        v -= 4;
    } while (v >= 0);
    D_801CF87E = func_8002398C(0, 2, 0x3C0, 0x100);
    D_801CF892 = func_8002398C(0, 1, 0x3C0, 0x100);
}
