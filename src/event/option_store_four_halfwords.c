#include "psx/types.h"

extern s16 g_option_text_blit_source_x;
extern s16 g_option_text_blit_source_y;
extern s16 g_option_text_blit_width;
extern s16 g_option_text_blit_height;

void option_store_four_halfwords(s16 source_x, s16 source_y, s16 width,
    s16 height) {
    g_option_text_blit_source_x = source_x;
    g_option_text_blit_source_y = source_y;
    g_option_text_blit_width = width;
    g_option_text_blit_height = height;
}
