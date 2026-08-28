#include "psx/types.h"

extern s32 D_801B69CC;
extern s32 D_801B69D0;
extern s32 D_801B69D4;
extern s32 D_801B8B18;
extern s32 D_801B8B1C;
extern void func_801AA920(void);

void battle_init_camera_and_screen_data(void) {
    s32 pad[2];
    D_801B69CC = 0;
    D_801B69D0 = 0;
    D_801B69D4 = 0;
    D_801B8B1C = 0;
    D_801B8B18 = 0;
    func_801AA920();
    (void)pad;
}
