#include "psx/types.h"

extern void wldcore_store_script_and_date(s32*, s32*, s32*, s32*);
extern s32 g_world_script_flags;

void world_map_script_0x11(void) {
    s32 a, b, c, d;
    s32* p;

    wldcore_store_script_and_date(&a, &b, &c, &d);
    if ((c > a) || ((c == a) && (d > b))) {
        p = &g_world_script_flags;
        *p = *p | 2;
    }
}
