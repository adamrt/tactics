#include "psx/gpu.h"

typedef struct {
    s16 x_load;
    s16 y_load;
    u16 width;
    u16 height;
    u16 x_screen_offset;
    u16 y_screen_offset;
} WorldImageLoadParameters;

typedef struct {
    s16 x;
    u16 y;
} WorldImageLocation;

/* Fill a WORLD textured quad from load and screen placement parameters. */
void world_image_loading_setup(POLY_FT4* primitive,
    const WorldImageLocation* base_load,
    const WorldImageLocation* base_screen,
    const WorldImageLoadParameters* parameters) {
    int texture_column;

    if ((primitive->code & 0x7c) == 0x64) {
        if (parameters->x_load >= 0) {
            texture_column = (u16)base_load->x & 0x3f;
            primitive->u0 = (u8)((texture_column << 2) + (u8)parameters->x_load);
            primitive->v0 = (u8)(base_load->y + parameters->y_load);
            primitive->x1 = (s16)parameters->width;
            primitive->y1 = (s16)parameters->height;
        }
        primitive->x0 = (s16)(base_screen->x + parameters->x_screen_offset);
        primitive->y0 = (s16)(base_screen->y + parameters->y_screen_offset);
        return;
    }

    if (parameters->x_load >= 0) {
        primitive->tpage = (u16)GetTPage(0, 0, base_load->x, base_load->y & 0xf00);
        primitive->u0 = (u8)parameters->x_load;
        primitive->v0 = (u8)(base_load->y + parameters->y_load);
        primitive->u1 = (u8)(parameters->x_load + parameters->width);
        primitive->v1 = (u8)(base_load->y + parameters->y_load);
        primitive->u2 = (u8)parameters->x_load;
        primitive->v2 = (u8)(base_load->y + parameters->y_load + parameters->height);
        primitive->u3 = (u8)(parameters->x_load + parameters->width);
        primitive->v3 = (u8)(base_load->y + parameters->y_load + parameters->height);
    }

    primitive->x0 = (s16)(base_screen->x + parameters->x_screen_offset);
    primitive->y0 = (s16)(base_screen->y + parameters->y_screen_offset);
    primitive->x1 = (s16)(base_screen->x + parameters->x_screen_offset + parameters->width);
    primitive->y1 = (s16)(base_screen->y + parameters->y_screen_offset);
    primitive->x2 = (s16)(base_screen->x + parameters->x_screen_offset);
    primitive->y2 = (s16)(base_screen->y + parameters->y_screen_offset + parameters->height);
    primitive->x3 = (s16)(base_screen->x + parameters->x_screen_offset + parameters->width);
    primitive->y3 = (s16)(base_screen->y + parameters->y_screen_offset + parameters->height);
}
