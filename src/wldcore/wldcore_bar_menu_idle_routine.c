#include "psx/types.h"

typedef struct {
    u8 data[92];
} BarMenuEntry;

extern s32 D_800BB4F0;
extern s32 D_800D4580[];
extern BarMenuEntry D_800BB930[];
extern void (*D_8009E690[])(BarMenuEntry*);

void wldcore_bar_menu_idle_routine(void) {
    s32 index;

    index = D_800BB4F0;
    D_8009E690[D_800D4580[index]](&D_800BB930[index]);
}
