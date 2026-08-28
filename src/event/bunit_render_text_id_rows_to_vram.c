#include "psx/gpu.h"
#include "psx/types.h"

extern void* memset(void*, s32, s32);
extern void func_801CB6BC(void* buf, RECT* rect, s32 a2, s32 a3, s32 a4, s16* chars, s32 a6, s32 a7, s32 a8);
extern void bunit_load_image_and_wait(RECT* rect, void* buf);

void bunit_render_text_id_rows_to_vram(s32 arg0, u16* list, RECT* src, s32 arg3) {
    u32 buf[0x200];
    RECT clear;
    RECT dest;
    s16 chars[2];

    clear.x = 0;
    clear.y = 0;
    clear.w = src->w;
    clear.h = 0x10;
    dest.x = src->x;
    dest.y = src->y;
    dest.w = src->w;
    dest.h = 0x10;

    while (*(s16*)list != -1) {
        chars[0] = *list;
        chars[1] = -1;
        memset(buf, 0, 0x800);
        func_801CB6BC(buf, &clear, 0xA, 0x64, arg0, chars, 0x64, 0xE7, arg3);
        bunit_load_image_and_wait(&dest, buf);
        dest.y += 0x10;
        list++;
    }
}
