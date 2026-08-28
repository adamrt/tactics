#include "psx/types.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} BunitZoomRect;

extern s8 g_bunit_transition_frame;
extern u32 D_801EC8B8;
extern s16 D_801CFA1C[];
extern s16 g_bunit_otag_index;
extern u8 g_bunit_otag_index_locked;
extern void bunit_enqueue_draw_area(BunitZoomRect* rect, s32 ot_index);
extern void func_801C8AF4(u8* p);

void bunit_parse_zoomed_draw_area(u8* p) {
    BunitZoomRect r;
    s32 frame;
    s32 scale;

    frame = g_bunit_transition_frame;
    if (frame < 4) {
        if (frame < 3) {
            D_801EC8B8 = 0;
        }
        scale = D_801CFA1C[frame];
        r.w = p[5] * scale / 100;
        r.h = p[6] * scale / 100;
        r.x = p[3] + (p[5] >> 1) - (r.w >> 1);
        r.y = p[4] + (p[6] >> 1) - (r.h >> 1);
        bunit_enqueue_draw_area(&r, g_bunit_otag_index - 1);
        g_bunit_otag_index_locked = 1;
    } else {
        g_bunit_otag_index_locked = 0;
    }
    func_801C8AF4(p);
}
