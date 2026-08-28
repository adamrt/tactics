#include "psx/types.h"

extern u8 g_open_file_header[];
extern void* g_open_file_destination;

extern void open_wait_then_build_file_header(
    void* header,
    s32 sector,
    s32 sector_count,
    void* destination);
extern void open_wait_for_pending_file(void);
extern void open_put_opntex_in_frame_buffer(void* data);
extern void open_build_openbk_file_header(s32 image_id, void* destination);

void open_load_main_menu_graphics(void) {
    void* header = g_open_file_header;

    open_wait_then_build_file_header(
        header, 0x1505d, 0x11, g_open_file_destination);
    open_wait_for_pending_file();
    open_put_opntex_in_frame_buffer(g_open_file_destination);

    open_wait_then_build_file_header(
        header, 0x1506e, 0x11, g_open_file_destination);
    open_wait_for_pending_file();
    open_put_opntex_in_frame_buffer(g_open_file_destination);

    open_wait_then_build_file_header(
        header, 0x1507f, 0x21, g_open_file_destination);
    open_wait_for_pending_file();
    open_put_opntex_in_frame_buffer(g_open_file_destination);

    open_build_openbk_file_header(0, g_open_file_destination);
    open_wait_for_pending_file();
}
