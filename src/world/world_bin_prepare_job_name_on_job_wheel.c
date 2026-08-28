#include "psx/types.h"

extern s16 g_world_job_wheel_job_count;
extern s16 g_world_job_wheel_cursor_index;
extern u16 g_world_job_wheel_jobs[];
extern s16 D_801C8450;
extern s16 D_801C8452;
extern s16 D_801C8454;
extern s16 D_801C8456;
extern u16 g_world_job_wheel_name_text;
extern u8* D_801CD8BC;
extern u8* D_801CD910;

extern void func_8012A5C0(u8* arg0, u16* arg1, s16* arg2, s32 arg3);
extern s32 world_find_text_entry_by_index(u8* arg0, s32 arg1, s32 arg2);
extern s8 func_8012A9D4(s32 arg0);

void world_bin_prepare_job_name_on_job_wheel(void) {
    s16 rect[4];
    u8* font;
    u16* name;
    u16 id;
    s32 width;

    if (g_world_job_wheel_job_count < 2) {
        font = D_801CD910;
        id = 0x1B;
    } else {
        font = D_801CD8BC;
        id = g_world_job_wheel_jobs[g_world_job_wheel_cursor_index];
    }
    g_world_job_wheel_name_text = id;
    __asm__ volatile("");
    name = &g_world_job_wheel_name_text;
    rect[0] = 0x24C;
    rect[1] = 0x130;
    rect[2] = 0x14;
    rect[3] = 0x10;
    func_8012A5C0(font, name, rect, 0);
    width = func_8012A9D4(world_find_text_entry_by_index(font, *name & 0x3FF, 2));
    D_801C8450 = ((0x50 - width) >> 1) + 0x58;
    D_801C8452 = 0xD7;
    D_801C8454 = width;
    D_801C8456 = 0xE;
}
