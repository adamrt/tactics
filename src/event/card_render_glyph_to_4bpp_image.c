#include "psx/types.h"

typedef struct CardTextImagePosition {
    u16 x;
    s16 y;
    s16 row_stride;
} CardTextImagePosition;

extern const u8* g_card_glyph_bitmap_data;
extern const u8 g_card_glyph_widths[];
extern void card_set_primary_bitstream(const void* data);
extern u32 card_read_primary_bits(s32 bit_count);

s32 card_render_glyph_to_4bpp_image(
    s32 glyph_id, u8* image, const CardTextImagePosition* position,
    s32 style) {
    s32 row;
    s32 palette_offset;
    const u8* glyph_bitmap;

    glyph_bitmap = g_card_glyph_bitmap_data;
    glyph_bitmap += glyph_id * 35;
    card_set_primary_bitstream(glyph_bitmap);

    row = 0;
    do {
        s32 byte_index;
        s32 stride;
        s32 destination_y;
        u8* destination;

        stride = position->row_stride * 2;
        destination_y = position->y + row;
        destination = image + stride * destination_y + ((s16)position->x >> 1);
        byte_index = 0;
        do {
            s32 pixel;
            /* Pins: target copies the read into $a0, adjusts in $v1 and shifts
             * into a fresh $v0; unpinned, local-alloc ties the shift to $v1
             * and coalesces the first nibble into $s0. */
            register s32 adjusted_pixel asm("$3");
            u8 low_pixel;
            register s32 high_nibble asm("$2");

            palette_offset = style << 2;
            pixel = card_read_primary_bits(2);
            adjusted_pixel = pixel;
            if ((u8)adjusted_pixel != 0) {
                adjusted_pixel = pixel + palette_offset;
            }
            low_pixel = adjusted_pixel;
            pixel = card_read_primary_bits(2);
            adjusted_pixel = pixel;
            if ((u8)adjusted_pixel != 0) {
                adjusted_pixel = pixel + palette_offset;
            }
            high_nibble = adjusted_pixel << 4;
            low_pixel |= high_nibble;
            *destination++ = low_pixel;
            byte_index++;
        } while (byte_index < 5);
        row++;
    } while (row < 14);

    return g_card_glyph_widths[glyph_id];
}
