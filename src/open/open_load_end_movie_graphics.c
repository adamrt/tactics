#include "psx/gpu.h"
#include "psx/types.h"

extern u8 g_open_file_header[];
extern void* g_open_file_destination;
extern void* g_open_opntex_data;

extern void open_wait_then_build_file_header(
    void* header,
    s32 sector,
    s32 sector_count,
    void* destination);
extern void open_wait_for_pending_file(void);
extern void open_put_opntex_in_frame_buffer(void* data);
extern void open_build_openbk_file_header(s32 image_id, void* destination);

void open_load_end_movie_graphics(void) {
    void* header = g_open_file_header;
    RECT frame;

    open_wait_then_build_file_header(
        header, 0x150c2, 0x11, g_open_file_destination);
    open_wait_for_pending_file();
    open_put_opntex_in_frame_buffer(g_open_file_destination);

    open_build_openbk_file_header(6, g_open_opntex_data);
    open_wait_for_pending_file();

    frame.x = 0x200;
    frame.y = 0x100;
    frame.w = 0x200;
    frame.h = 0xf0;
    LoadImage(&frame, g_open_opntex_data);
    DrawSync(0);

    open_wait_then_build_file_header(
        header, 0x150d3, 0x170, g_open_opntex_data);
    open_wait_for_pending_file();
}
