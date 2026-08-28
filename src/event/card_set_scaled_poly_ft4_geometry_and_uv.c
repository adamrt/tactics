#include "psx/gpu.h"
#include "psx/types.h"

typedef struct CardTexturePage {
    s16 x;
    u16 y;
} CardTexturePage;

void card_set_scaled_poly_ft4_geometry_and_uv(
    POLY_FT4* poly, const CardTexturePage* texture, const s16* position,
    const s16* uv_rect, const s16* scale, const s16* offset) {
    s32 xoff = uv_rect[4] * scale[0];
    s32 yoff = uv_rect[5] * scale[1];
    s32 width = uv_rect[2] * scale[0];
    s32 height = uv_rect[3] * scale[1];
    s32 round_xoff = 0;
    s32 round_yoff = 0;
    s32 round_width = 0;
    s32 round_height = 0;
    s32 xoff_quotient;
    s32 yoff_quotient;
    s32 width_quotient;
    s32 height_quotient;

    xoff_quotient = xoff / 4096;
    if (xoff - xoff_quotient * 4096 >= 2048)
        round_xoff = 1;
    yoff_quotient = yoff / 4096;
    if (yoff - yoff_quotient * 4096 >= 2048)
        round_yoff = 1;
    width_quotient = width / 4096;
    if (width - width_quotient * 4096 >= 2048)
        round_width = 1;
    height_quotient = height / 4096;
    if (height - height_quotient * 4096 >= 2048)
        round_height = 1;
    xoff = xoff_quotient + round_xoff;
    yoff = yoff_quotient + round_yoff;
    width = width_quotient + round_width;
    height = height_quotient + round_height;
    if (width < 0)
        width = -width;
    if (height < 0)
        height = -height;

    poly->tpage = GetTPage(1, 0, texture->x, texture->y & 0xf00);
    poly->u0 = (u8)uv_rect[0];
    poly->v0 = (u8)uv_rect[1];
    poly->u1 = (u8)uv_rect[0] + (u8)uv_rect[2];
    poly->v1 = (u8)uv_rect[1];
    poly->u2 = (u8)uv_rect[0];
    poly->v2 = (u8)uv_rect[1] + (u8)uv_rect[3];
    poly->u3 = (u8)uv_rect[0] + (u8)uv_rect[2];
    poly->v3 = (u8)uv_rect[1] + (u8)uv_rect[3];
    poly->x0 = position[0] + xoff + offset[4];
    poly->y0 = position[1] + yoff + offset[5];
    poly->x1 = position[0] + xoff + offset[4] + width;
    poly->y1 = position[1] + yoff + offset[5];
    poly->x2 = position[0] + xoff + offset[4];
    poly->y2 = position[1] + yoff + offset[5] + height;
    poly->x3 = position[0] + xoff + offset[4] + width;
    poly->y3 = position[1] + yoff + offset[5] + height;
}
