#include "psx/types.h"

typedef struct BunitRect {
    /* 0x00 */ u8 pad_00[8];
    /* 0x08 */ u16 h_08;
    /* 0x0A */ u8 pad_0a[2];
    /* 0x0C */ u8 b_0c;
    /* 0x0D */ u8 pad_0d[7];
    /* 0x14 */ u8 b_14;
    /* 0x15 */ u8 b_15;
    /* 0x16 */ u8 pad_16[2];
    /* 0x18 */ u16 h_18;
    /* 0x1A */ u8 pad_1a[10];
    /* 0x24 */ u8 b_24;
    /* 0x25 */ u8 b_25;
} BunitRect;

/* BUNIT.OUT 001bf4c8 - Shift a menu rect by `delta` on one axis, and shrink either
 * the horizontal or vertical extent depending on whether width equals height. */
void bunit_clip_portrait_poly_from_left(BunitRect* r, s32 delta) {
    r->h_08 = r->h_08 + delta;
    r->h_18 = r->h_18 + delta;
    if (r->b_0c != r->b_14) {
        r->b_14 = r->b_14 - delta;
        r->b_24 = r->b_24 - delta;
        return;
    }
    r->b_15 = r->b_15 - delta;
    r->b_25 = r->b_25 - delta;
}
