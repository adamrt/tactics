#include "psx/gpu.h"
#include "psx/types.h"

extern s16 g_jobstts_list_row_rendering;
extern s16 g_jobstts_list_row_height;
extern s32 g_jobstts_list_row_index;
extern s16 g_jobstts_list_scroll_offset_y;
extern u8 g_jobstts_text_color[];
extern s16 g_jobstts_otag_index;
extern s16 g_jobstts_semitransparency;
extern u16 g_jobstts_texture_page;
extern u16 g_jobstts_clut_id;

extern void jobstts_out_build_board_polygons(RECT*, u8, u8, u8*, s32, s32, s32, s32);

u8* jobstts_out_create_column_headings_separators_mastered_graph(u8* data) {
    RECT rect;
    s32 y;
    u8* pal;

    if (g_jobstts_list_row_rendering == 0) {
        y = data[4];
    } else {
        y = ((g_jobstts_list_row_height * g_jobstts_list_row_index) + data[4]) - g_jobstts_list_scroll_offset_y;
        if (g_jobstts_list_scroll_offset_y < 0) {
            y -= g_jobstts_list_row_height;
        }
    }
    rect.x = data[3];
    rect.y = y;
    rect.w = data[5];
    rect.h = data[6];
    pal = g_jobstts_text_color;
    if (data[0] == 4) {
        pal = 0;
    }
    jobstts_out_build_board_polygons(&rect, data[7], data[8], pal, g_jobstts_semitransparency, g_jobstts_texture_page, g_jobstts_clut_id, g_jobstts_otag_index);
    return data + data[1];
}
