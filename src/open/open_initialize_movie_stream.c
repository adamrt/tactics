#include "psx/types.h"

extern void DecDCTReset(s32 mode);
extern void DecDCToutCallback(void* callback);
extern void StSetRing(void* buffer, s32 sectors);
extern void StSetStream(s32 mode, s32 start_frame, s32 end_frame,
    void* start_callback, void* end_callback);
extern void main_build_file_header_nnl(void* header, s32 sector, s32 sector_count,
    void* destination);
extern void open_file_to_ram_center(void* header);
extern s32 VSync(s32 mode);
extern s32 CdControl(s32 command, const void* parameter, void* result);

extern u8 g_open_cd_stream_ring_buffer[];
extern u8 g_open_file_header[];
extern u8 g_open_file_location[];
extern s32 g_open_pending_file_status;

void open_initialize_movie_stream(s32 sector, void* output_callback) {
    u8* header;

    DecDCTReset(0);
    DecDCToutCallback(output_callback);
    StSetRing(g_open_cd_stream_ring_buffer, 0x30);
    StSetStream(1, 0, -1, 0, 0);

    header = g_open_file_header;
    main_build_file_header_nnl(header, sector, 1, 0);
    while (g_open_pending_file_status != 0) {
        open_file_to_ram_center(header);
        VSync(0);
    }

    while (CdControl(2, g_open_file_location, 0) == 0) {
    }
}
