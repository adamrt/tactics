#include "psx/gpu.h"

extern RECT g_world_texture_window;

/* Select the WORLD image texture page and initialize its draw mode. */
void world_set_image_draw_mode(DR_MODE* mode, s32 image_type) {
    /* Unpinned, GCC homes the page in $a3 and adds a `move a3,v0` after the
     * GetTPage call; the target masks straight from $v0. */
    register s32 texture_page __asm__("$2");

    if (image_type == 0) {
        texture_page = GetTPage(0, 0, 960, 256);
    } else if (image_type == 1) {
        texture_page = GetTPage(0, 0, 448, 0);
    } else if (image_type == 2) {
        texture_page = GetTPage(0, 0, 384, 0);
    } else if (image_type == 3) {
        texture_page = GetTPage(0, 0, 832, 256);
    } else {
        texture_page = GetTPage(0, 0, 896, 288);
    }
    SetDrawMode(mode, 0, 0, (u16)texture_page, &g_world_texture_window);
}
