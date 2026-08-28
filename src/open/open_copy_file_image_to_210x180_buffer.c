#include "psx/types.h"

#define OPEN_IMAGE_COPY_WIDTH  210
#define OPEN_IMAGE_COPY_HEIGHT 180

extern u8* g_open_file_destination;
extern u16* g_open_image_copy_source_buffer;
extern u16* volatile g_open_image_copy_destination_buffer;
extern u16* volatile g_open_image_copy_file_pixels;
extern u8 g_open_image_copy_row_flags[];
extern u16 g_open_work_buffer_0[];
extern u16 g_open_work_buffer_1[];

void open_build_openbk_file_header(s32 file_index);

void open_copy_file_image_to_210x180_buffer(s32 file_index) {
    /* Two pins: GCC otherwise allocates the source buffer $v0 (target $a1)
     * and the destination index $a0 (target $v1). */
    register u16* copy_source __asm__("$5");
    u16* copy_destination;
    u16* file_pixels;
    s32 row;
    s32 source_row;
    s32 column;
    s32 source_offset;
    register s32 destination_index __asm__("$3");
    s32 source_index;
    s32 destination_offset;
    u16* pixels;
    u16 value;

    copy_source = g_open_work_buffer_0;
    copy_destination = g_open_work_buffer_1;
    file_pixels = (u16*)(g_open_file_destination + 0x5600);
    g_open_image_copy_source_buffer = copy_source;
    g_open_image_copy_destination_buffer = copy_destination;
    g_open_image_copy_file_pixels = file_pixels;
    open_build_openbk_file_header(file_index + 2);

    row = 0;
    source_row = 0;
    do {
        column = 0;
        source_offset = row << 8;
        do {
            destination_index = source_row + column;
            source_index = source_offset + column;
            column++;
            destination_index <<= 1;
            pixels = g_open_image_copy_file_pixels;
            /* Zero-byte fence: the source scale (sll) is emitted after the
             * volatile pointer reload, the destination scale before it. */
            __asm__ volatile("");
            source_index <<= 1;
            /* index + (u32)pointer: the retail addu sums index first. */
            value = *(u16*)(source_index + (u32)pixels);
            *(u16*)(destination_index + (u32)g_open_image_copy_destination_buffer) = value;
        } while (column < OPEN_IMAGE_COPY_WIDTH);
        g_open_image_copy_row_flags[row + 2] = 0;
        row++;
        source_row += OPEN_IMAGE_COPY_WIDTH;
    } while (row < OPEN_IMAGE_COPY_HEIGHT);

    g_open_image_copy_row_flags[0] = 0;
    g_open_image_copy_row_flags[1] = 0;
}
