#include "psx/gpu.h"

extern s8 g_jobstts_otag_index_locked;
extern s16 g_jobstts_otag_index;
extern RECT g_jobstts_draw_area;
extern void jobstts_enqueue_draw_area(RECT* destination, s32 value);

const u8* jobstts_parse_add_next_otag_draw_area(const u8* data) {
    if (g_jobstts_otag_index_locked == 0) {
        g_jobstts_draw_area.y = 0;
        jobstts_enqueue_draw_area(&g_jobstts_draw_area, g_jobstts_otag_index + 1);
    }
    return data + data[1];
}
