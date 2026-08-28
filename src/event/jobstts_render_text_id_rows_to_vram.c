#include "psx/gpu.h"
#include "psx/types.h"

extern void memset(void*, s32, s32);
extern void func_801E079C(u32*, RECT*, s32, s32, s32, s16*, s32, s32, s32);
extern void jobstts_load_image_and_wait(RECT*, u32*);

void jobstts_render_text_id_rows_to_vram(s32 arg0, s16* arg1, RECT* arg2, s32 arg3) {
    u32 buffer[0x200];
    RECT src;
    RECT dst;
    s16 ids[2];

    src.x = 0;
    src.y = 0;
    src.w = arg2->w;
    src.h = 0x10;
    dst.x = arg2->x;
    dst.y = arg2->y;
    dst.w = arg2->w;
    dst.h = 0x10;
    while (*arg1 != -1) {
        ids[0] = *arg1;
        ids[1] = -1;
        memset(buffer, 0, 0x800);
        func_801E079C(buffer, &src, 0xA, 0x64, arg0, ids, 0x64, 0xE7, arg3);
        jobstts_load_image_and_wait(&dst, buffer);
        arg1 += 1;
        dst.y += 0x10;
    }
}
