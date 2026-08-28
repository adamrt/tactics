#include "psx/types.h"

extern void func_800E1534(void);
extern s32 D_801CD74C;
extern s32 D_801CD760;
extern s16 D_801CD508;
extern s16 D_801CD50A;
extern s32 D_801CD854;
extern s32 D_801CD83C;
extern s32 D_801CD7DC;

void world_gs_init3d(void) {
    D_801CD508 = (s16)(D_801CD74C / 2);
    D_801CD50A = (s16)(D_801CD760 / 2);
    func_800E1534();
    D_801CD854 = 0xA;
    D_801CD83C = 0;
    D_801CD7DC = 0x3FFF;
}
/* padpadpadpadpadpadpadpadpadpadpadpadpadpadpadpadpadpadpadpadpadpadpadpadpad */
