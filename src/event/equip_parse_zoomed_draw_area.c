#include "psx/types.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} EquipZoomRect;

extern s8 g_equip_transition_frame;
extern u32 D_801E9000;
extern s16 D_801D8784[];
extern s16 g_equip_sprite_ot_index;
extern u8 g_equip_zoom_draw_area_active;
extern void func_801CA648(EquipZoomRect* rect, s32 ot_index);
extern void func_801CB08C(u8* p);

void equip_parse_zoomed_draw_area(u8* p) {
    EquipZoomRect r;
    s32 frame;
    s32 scale;

    frame = g_equip_transition_frame;
    if (frame < 4) {
        if (frame < 3) {
            D_801E9000 = 0;
        }
        scale = D_801D8784[frame];
        r.w = p[5] * scale / 100;
        r.h = p[6] * scale / 100;
        r.x = p[3] + (p[5] >> 1) - (r.w >> 1);
        r.y = p[4] + (p[6] >> 1) - (r.h >> 1);
        func_801CA648(&r, g_equip_sprite_ot_index - 1);
        g_equip_zoom_draw_area_active = 1;
    } else {
        g_equip_zoom_draw_area_active = 0;
    }
    func_801CB08C(p);
}
