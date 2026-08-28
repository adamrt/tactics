#include "psx/types.h"

extern s32 g_open_current_openbk_image_id;
extern u8 g_open_file_header[];
extern const s32 g_open_openbk_start_sector_offsets[];
extern const s32 g_open_openbk_end_sector_offsets[];

extern void open_wait_then_build_file_header(
    void* header,
    s32 sector,
    s32 sector_count,
    void* destination);

/* OPENBK images live in one contiguous sector run starting at 0x15243. */
#define OPEN_OPENBK_BASE_SECTOR 0x15243

void open_build_openbk_file_header(s32 image_id, void* destination) {
    s32 start_offset;
    s32 end_offset;
    s32 stack_padding[2];

    if (image_id == g_open_current_openbk_image_id) {
        return;
    }

    g_open_current_openbk_image_id = image_id;
    start_offset = g_open_openbk_start_sector_offsets[image_id];
    end_offset = g_open_openbk_end_sector_offsets[image_id];
    open_wait_then_build_file_header(
        g_open_file_header,
        OPEN_OPENBK_BASE_SECTOR + start_offset,
        end_offset - start_offset,
        destination);
}
