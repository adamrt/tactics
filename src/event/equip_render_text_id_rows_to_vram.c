#include "psx/gpu.h"
#include "psx/types.h"

extern void memset(void* dst, s32 value, s32 len);
extern void func_801C8B24(u32* buf, RECT* rect, s32 arg2, s32 arg3, void* arg4,
    s16* text, s32 arg6, s32 arg7, s32 arg8);
extern void equip_load_image_and_wait(RECT* rect, u32* data);

void equip_render_text_id_rows_to_vram(void* arg0, s16* list, RECT* src, s32 arg3) {
    u32 buf[0x200];
    RECT clear_rect;
    RECT dest_rect;
    s16 text[4];

    clear_rect.x = 0;
    clear_rect.y = 0;
    clear_rect.w = src->w;
    clear_rect.h = 0x10;

    dest_rect.x = src->x;
    dest_rect.y = src->y;
    dest_rect.w = src->w;
    dest_rect.h = 0x10;

    while (*list != -1) {
        text[0] = *list;
        text[1] = -1;
        memset(buf, 0, 0x800);
        func_801C8B24(buf, &clear_rect, 0xa, 0x64, arg0, text, 0x64, 0xeb, arg3);
        equip_load_image_and_wait(&dest_rect, buf);
        dest_rect.y += 0x10;
        list++;
    }
}
