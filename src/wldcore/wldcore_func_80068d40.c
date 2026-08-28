#include "psx/types.h"

extern u8 g_cd_file_state;
extern s32 D_800459C8;

extern void func_800685E0(u8* state, s32 arg1, s32 arg2, s32 arg3);

void wldcore_func_80068d40(void) {
    func_800685E0(&g_cd_file_state, D_800459C8, 1, 0);
}
