#include "psx/types.h"

extern s16 g_world_image_blit_destination_x;
extern s16 g_world_image_blit_destination_y;

/* Set the destination origin used by the WORLD image blitter. */
void world_set_image_blit_destination_origin(s16 x, s16 y) {
    g_world_image_blit_destination_x = x;
    g_world_image_blit_destination_y = y;
}
