#include "psx/types.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} BunitRect;

typedef struct {
    u8 data[0x200];
} BunitBlock200;

extern BunitBlock200 D_801BF000;
extern void* D_80173F8C;
extern void* D_80173FF0;
extern void* D_80173F5C;
extern s32 D_801CF458;
extern s32 D_801EB158;
extern s32 g_bunit_selection_text_id;
extern s32 D_801ECB68;

extern void bunit_set_event_speed(s32 speed);
extern void bunit_load_image_and_wait(BunitRect*, void*);
extern void bunit_store_image_and_wait(BunitRect*, void*);
extern void bunit_start_fade_from_0xf0(void);

void bunit_init_vram_and_start_fade(void) {
    BunitRect rect;
    u16 buf1[4];
    u16 buf2[12];
    BunitBlock200 block = D_801BF000;

    bunit_set_event_speed(0);
    D_80173F8C = &D_801CF458;
    D_80173FF0 = &D_801EB158;
    rect.x = 0x100;
    rect.y = 0;
    rect.w = 0x40;
    rect.h = 0x30;
    bunit_load_image_and_wait(&rect, D_80173F5C);
    rect.x = 0x3C0;
    rect.y = 0x1F0;
    rect.w = 0x10;
    rect.h = 1;
    bunit_store_image_and_wait(&rect, buf1);
    buf2[0] = 0;
    rect.x = 0x120;
    rect.y = 0xFE;
    rect.w = 0x10;
    rect.h = 1;
    bunit_load_image_and_wait(&rect, buf1);
    rect.x = 0x100;
    rect.y = 0xFE;
    rect.w = 0xC;
    rect.h = 1;
    bunit_load_image_and_wait(&rect, buf2);
    rect.x = 0x3C0;
    rect.y = 0x1F4;
    rect.w = 0x10;
    rect.h = 1;
    bunit_store_image_and_wait(&rect, buf1);
    buf2[0] = 0;
    rect.x = 0x130;
    rect.y = 0xFE;
    rect.w = 0x10;
    rect.h = 1;
    bunit_load_image_and_wait(&rect, buf1);
    rect.x = 0x110;
    rect.y = 0xFE;
    rect.w = 0xC;
    rect.h = 1;
    bunit_load_image_and_wait(&rect, buf2);
    rect.x = 0x100;
    rect.y = 0xFA;
    rect.w = 0x40;
    rect.h = 4;
    bunit_load_image_and_wait(&rect, &block);
    g_bunit_selection_text_id = 0;
    D_801ECB68 = 0;
    bunit_start_fade_from_0xf0();
}
