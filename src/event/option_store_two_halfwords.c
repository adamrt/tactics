#include "psx/types.h"

extern s16 g_option_text_blit_destination_x;
extern s16 g_option_text_blit_destination_y;

void option_store_two_halfwords(s16 destination_x, s16 destination_y) {
    g_option_text_blit_destination_x = destination_x;
    g_option_text_blit_destination_y = destination_y;
}
