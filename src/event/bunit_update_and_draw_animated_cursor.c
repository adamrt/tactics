#include "psx/types.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} BunitRect;

extern s8 D_801CFA44[];
extern u8 D_801CFA44U[];
extern s8 D_801CFA38[];
extern u8 D_801CFA38U[];
extern u16 D_801CF972;
extern u16 D_801CF974;
extern u16 D_801CF96E;
extern u16 D_801CF970;
extern u16 D_801CF95E;

extern s32 bunit_get_event_speed(void);
extern void bunit_enqueue_textured_quad(BunitRect* rect, s32 u, s32 v,
    const u8* color, s32 semitrans,
    u16 texture_page, u16 clut,
    s32 otag_index);

void bunit_update_and_draw_animated_cursor(u16* pos, u16* state, s32 mode) {
    BunitRect rect;
    s32 active;
    s32 tmp;
    s32 timer;
    s32 offset;
    s32 shifted;
    s32 i;
    u16 clut0;
    u16 clut1;

    tmp = state[0] >> 15;
    active = tmp;
    if (mode == 0) {
        if (tmp != 0) {
            state[0] = 0;
            active = 0;
        }
    }
    tmp = active;
    if (tmp == 0 && (mode & 1) != 0) {
        state[0] = 0x8000;
        active = 1;
    }

    timer = state[0];
    timer &= 0x7F;
    timer = timer * bunit_get_event_speed();
    tmp = active;
    if (tmp != 0) {
        if (timer >= 0x25) {
            timer = 0x24;
        }
    } else {
        if (timer >= 0x2F) {
            timer = 0;
        }
    }

    tmp = active;
    if (tmp != 0) {
        for (i = 0; D_801CFA44[i] < timer; i += 2) {
        }
        shifted = D_801CFA44U[i + 1] << 24;
    } else {
        for (i = 0; D_801CFA38[i] < timer; i += 2) {
        }
        shifted = D_801CFA38U[i + 1] << 24;
    }

    offset = shifted >> 24;
    timer += bunit_get_event_speed();
    tmp = active;
    if (tmp != 0) {
        if (timer < 0x25) {
            state[0]++;
        }
    } else {
        if (timer < 0x2F) {
            state[0]++;
        } else {
            state[0] = 0;
        }
    }

    if (mode != 0) {
        clut0 = D_801CF972;
        clut1 = D_801CF974;
    } else {
        clut0 = D_801CF96E;
        clut1 = D_801CF970;
    }

    rect.x = offset + pos[0] - 2;
    rect.y = pos[1];
    rect.w = 0x10;
    rect.h = 0x10;
    bunit_enqueue_textured_quad(&rect, 0xA8, 0, 0, 0, D_801CF95E, clut0, 0x3C);
    rect.x += 2;
    rect.y += 2;
    bunit_enqueue_textured_quad(&rect, 0xB8, 0, 0, 1, 0x5F, clut1, 0x3B);
}
