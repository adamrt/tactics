#include "psx/types.h"

extern u16 g_world_draw_suppress_flag;

/* Paired with world_set_draw_suppress_flag (0x800e8a34).  While the flag is non-zero the world
   display thread at 0x800e8ab0 skips its four primitive submissions. */
void world_clear_draw_suppress_flag(void) {
    g_world_draw_suppress_flag = 0;
}
