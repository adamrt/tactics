#include "psx/types.h"

extern u8 D_8018E494;
extern u8 g_world_fade_disabled;
extern u8 D_8018E496;
extern s16 D_801CA760;

void world_func_8012d48c(void) {
    if (g_world_fade_disabled == 0) {
        D_8018E494 = 0;
        D_8018E496 = 1;
        D_801CA760 = 0;
    }
}
