#include "psx/types.h"

extern s16 g_world_image_blit_source_x;
extern s16 g_world_image_blit_source_y;
extern s16 g_world_image_blit_source_width;
extern s16 g_world_image_blit_source_height;

/* Set the source rectangle used by the WORLD image blitter. */
void world_set_image_blit_source_rect(s16 x, s16 y, s16 width, s16 height) {
    g_world_image_blit_source_x = x;
    g_world_image_blit_source_y = y;
    g_world_image_blit_source_width = width;
    g_world_image_blit_source_height = height;
}
