#include "psx/types.h"

extern s8 g_jobstts_otag_index_locked;
extern s16 g_jobstts_otag_index;
extern void jobstts_enqueue_draw_area(s16* area, s32 otag);

u8* jobstts_parse_set_draw_area_if_unlocked(u8* data) {
    s16 area[4];

    if (g_jobstts_otag_index_locked == 0) {
        area[0] = data[2];
        area[1] = data[3];
        area[2] = data[4];
        area[3] = data[5];
        jobstts_enqueue_draw_area(area, g_jobstts_otag_index - 1);
    }
    return data + data[1];
}
