#include "psx/gpu.h"

void require_configure_scaled_poly_ft4(POLY_FT4* poly, const s16* texture,
    const s16* position,
    const s16* dimensions,
    const s16* scale, const s16* offset) {
    POLY_FT4* output = poly;
    const s16* output_position = position;
    const s16* texture_dimensions = dimensions;
    const s16* position_offset = offset;
    s32 x_offset;
    s32 y_offset;
    s32 width;
    s32 height;
    s32 x_product;
    s32 y_product;
    s32 width_product;
    s32 height_product;
    register s32 coordinate asm("$2");

    x_product = texture_dimensions[4] * scale[0];
    if (x_product < 0)
        x_product += 0xfff;
    x_offset = x_product >> 12;
    y_product = texture_dimensions[5] * scale[1];
    if (y_product < 0)
        y_product += 0xfff;
    y_offset = y_product >> 12;
    width_product = texture_dimensions[2] * scale[0];
    if (width_product < 0)
        width_product += 0xfff;
    width = width_product >> 12;
    height_product = texture_dimensions[3] * scale[1];
    if (height_product < 0)
        height_product += 0xfff;
    height = height_product >> 12;
    if (width < 0)
        width = -width;
    if (height < 0)
        height = -height;

    output->tpage = GetTPage(0, 0, texture[0], ((const u16*)texture)[1] & 0xf00);
    output->u0 = (u8)texture_dimensions[0];
    output->v0 = (u8)texture_dimensions[1];
    output->u1 = (u8)(texture_dimensions[0] + texture_dimensions[2]);
    output->v1 = (u8)texture_dimensions[1];
    output->u2 = (u8)texture_dimensions[0];
    output->v2 = (u8)(texture_dimensions[1] + texture_dimensions[3]);
    output->u3 = (u8)(texture_dimensions[0] + texture_dimensions[2]);
    output->v3 = (u8)(texture_dimensions[1] + texture_dimensions[3]);
    coordinate = (u16)output_position[0];
    coordinate += x_offset;
    coordinate += (u16)position_offset[4];
    output->x0 = coordinate;
    coordinate = (u16)output_position[1];
    coordinate += y_offset;
    coordinate += (u16)position_offset[5];
    output->y0 = coordinate;
    coordinate = (u16)output_position[0];
    coordinate += x_offset;
    coordinate += (u16)position_offset[4];
    coordinate += width;
    output->x1 = coordinate;
    coordinate = (u16)output_position[1];
    coordinate += y_offset;
    coordinate += (u16)position_offset[5];
    output->y1 = coordinate;
    coordinate = (u16)output_position[0];
    coordinate += x_offset;
    coordinate += (u16)position_offset[4];
    output->x2 = coordinate;
    coordinate = (u16)output_position[1];
    coordinate += y_offset;
    coordinate += (u16)position_offset[5];
    coordinate += height;
    output->y2 = coordinate;
    coordinate = (u16)output_position[0];
    coordinate += x_offset;
    coordinate += (u16)position_offset[4];
    coordinate += width;
    output->x3 = coordinate;
    coordinate = (u16)output_position[1];
    coordinate += y_offset;
    coordinate += (u16)position_offset[5];
    coordinate += height;
    output->y3 = coordinate;
}
