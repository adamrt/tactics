#include "fft/opening.h"

/* Record coordinates are quarter-pixel values; x also selects a 64-pixel
 * page before the upload is placed in VRAM at x 0x180. */
void open_upload_birthday_window_image(s32 record_index, u32* image) {
    RECT destination;
    s32 x;
    s32 depth;
    s32 scaled;

    x = g_open_render_records_56[record_index].tail.quad.x / 4;
    depth = g_open_render_records_56[record_index].depth;
    scaled = (depth << 6) + 0x180;
    destination.x = x + scaled;
    destination.y = g_open_render_records_56[record_index].tail.quad.y;
    destination.w = g_open_render_records_56[record_index].tail.quad.w / 4;
    destination.h = g_open_render_records_56[record_index].tail.quad.h;
    LoadImage(&destination, image);
}
