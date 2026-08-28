#include "psx/types.h"

extern s8 g_jobstts_otag_index_locked;
extern u16 g_jobstts_otag_index;
extern s16 g_jobstts_draw_area[];
extern void jobstts_enqueue_draw_area(s16* area, s16 otag_index);

u8* jobstts_parse_release_otag_lock_and_add_draw_area(u8* data) {
    u16 otag_index;
    if (g_jobstts_otag_index_locked != 0) {
        otag_index = g_jobstts_otag_index + 1;
        g_jobstts_draw_area[1] = 0;
        g_jobstts_otag_index = otag_index;
        jobstts_enqueue_draw_area(g_jobstts_draw_area, (s16)otag_index);
        g_jobstts_otag_index_locked = 0;
        g_jobstts_otag_index = g_jobstts_otag_index + 1;
    }
    return data + data[1];
}
