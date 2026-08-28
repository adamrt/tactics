#include "psx/gpu.h"

extern u8* g_battle_text_pointers[];
extern u8 D_801E502C[];
extern s32 g_jobstts_selected_job_text_id;

extern void jobstts_load_image_and_wait(RECT* rect, u32* data);
extern void jobstts_store_image_and_wait(RECT* rect, u32* data);
extern void jobstts_clear_input_repeat_counters(void);

void jobstts_out_001df004_001df194(void) {
    RECT rect;
    u16 buf[16];

    rect.x = 0x100;
    rect.y = 0;
    rect.w = 0x40;
    rect.h = 0x30;
    jobstts_load_image_and_wait(&rect, (u32*)g_battle_text_pointers[0]);

    rect.x = 0x100;
    rect.y = 0xfa;
    rect.w = 0x40;
    rect.h = 4;
    jobstts_load_image_and_wait(&rect, (u32*)D_801E502C);

    rect.x = 0x3c0;
    rect.y = 0x1f0;
    rect.w = 0x10;
    rect.h = 1;
    jobstts_store_image_and_wait(&rect, (u32*)&buf[0]);

    buf[4] = 0;
    rect.x = 0x120;
    rect.y = 0xfe;
    rect.w = 0x10;
    rect.h = 1;
    jobstts_load_image_and_wait(&rect, (u32*)&buf[0]);

    rect.x = 0x100;
    rect.y = 0xfe;
    rect.w = 0xc;
    rect.h = 1;
    jobstts_load_image_and_wait(&rect, (u32*)&buf[4]);

    rect.x = 0x3c0;
    rect.y = 0x1f4;
    rect.w = 0x10;
    rect.h = 1;
    jobstts_store_image_and_wait(&rect, (u32*)&buf[0]);

    buf[4] = 0;
    rect.x = 0x130;
    rect.y = 0xfe;
    rect.w = 0x10;
    rect.h = 1;
    jobstts_load_image_and_wait(&rect, (u32*)&buf[0]);

    rect.x = 0x110;
    rect.y = 0xfe;
    rect.w = 0xc;
    rect.h = 1;
    jobstts_load_image_and_wait(&rect, (u32*)&buf[4]);

    jobstts_clear_input_repeat_counters();
    g_jobstts_selected_job_text_id = 0;
}
