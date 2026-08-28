#include "psx/gpu.h"
#include "psx/types.h"

void battle_flip_poly_ft4_uv_if_negative(POLY_FT4* primitive, s32 direction) {
    u8 first;
    /* Pins: unpinned, GCC swaps `first` and `third` between $a1 and $v0
     * (all six declaration orders tried); the instruction stream is otherwise
     * identical. */
    register u8 second __asm__("$3");
    register u8 third __asm__("$2");

    if (direction < 0) {
        if (primitive->u0 != primitive->u1) {
            first = primitive->u0;
            second = primitive->u1;
            third = primitive->u3;
            primitive->u1 = first;
            first = primitive->u2;
            primitive->u0 = second;
            primitive->u2 = third;
            primitive->u3 = first;
        } else {
            first = primitive->v0;
            second = primitive->v1;
            third = primitive->v3;
            primitive->v1 = first;
            first = primitive->v2;
            primitive->v0 = second;
            primitive->v2 = third;
            primitive->v3 = first;
        }
    }
}
