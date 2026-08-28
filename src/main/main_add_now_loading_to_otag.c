#include "psx/gpu.h"

extern u32 g_now_loading_visible;
extern u32 g_screen_polarity;
extern u32 g_now_loading_frame_counter;
extern u8 g_now_loading_primitives[][7][40];

void main_add_now_loading_to_otag(u32 arg0) {
    int i;

    if (g_now_loading_visible != 0) {
        if (((g_now_loading_frame_counter / 60) & 1) == 0) {
            for (i = 0; i < 7; i++) {
                AddPrim(arg0, g_now_loading_primitives[g_screen_polarity][i]);
            }
        }
        g_now_loading_frame_counter++;
    }
}
