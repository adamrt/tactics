#include "psx/gpu.h"
#include "psx/types.h"

void require_scale_poly_gt4_vertex_colors(const u8* vertex_colors, s32 scale,
    POLY_GT4* poly) {
    s32 value;
    s32 red;
    register s32 blue __asm__("$2");

    value = vertex_colors[0x04] * scale;
    if (value < 0)
        value += 0x7f;
    red = value >> 7;
    value = vertex_colors[0x05] * scale;
    if (value < 0)
        value += 0x7f;
    blue = vertex_colors[0x06] * scale;
    if (blue < 0)
        blue += 0x7f;
    poly->r0 = red;
    poly->g0 = value >> 7;
    poly->b0 = blue >> 7;

    value = vertex_colors[0x08] * scale;
    if (value < 0)
        value += 0x7f;
    red = value >> 7;
    value = vertex_colors[0x09] * scale;
    if (value < 0)
        value += 0x7f;
    blue = vertex_colors[0x0a] * scale;
    if (blue < 0)
        blue += 0x7f;
    poly->r1 = red;
    poly->g1 = value >> 7;
    poly->b1 = blue >> 7;

    value = vertex_colors[0x0c] * scale;
    if (value < 0)
        value += 0x7f;
    red = value >> 7;
    value = vertex_colors[0x0d] * scale;
    if (value < 0)
        value += 0x7f;
    blue = vertex_colors[0x0e] * scale;
    if (blue < 0)
        blue += 0x7f;
    poly->r2 = red;
    poly->g2 = value >> 7;
    poly->b2 = blue >> 7;

    value = vertex_colors[0x10] * scale;
    if (value < 0)
        value += 0x7f;
    red = value >> 7;
    value = vertex_colors[0x11] * scale;
    if (value < 0)
        value += 0x7f;
    blue = vertex_colors[0x12] * scale;
    if (blue < 0)
        blue += 0x7f;
    poly->r3 = red;
    poly->g3 = value >> 7;
    poly->b3 = blue >> 7;
}
