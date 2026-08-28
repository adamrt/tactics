#include "psx/types.h"

extern u8 g_card_primary_bitstream_reset;
extern s32 g_card_bit_writer_1_index;
extern u8* g_card_primary_bitstream_cursor;

void card_write_primary_bit(s32 value) {
    s32 bit_index;
    u8 mask;

    if (g_card_primary_bitstream_reset != 0) {
        g_card_bit_writer_1_index = 7;
        g_card_primary_bitstream_reset = 0;
    }
    bit_index = g_card_bit_writer_1_index;
    g_card_bit_writer_1_index = bit_index - 1;
    mask = 1 << bit_index;
    *g_card_primary_bitstream_cursor &= ~mask;
    if ((value & 0xff) != 0) {
        *g_card_primary_bitstream_cursor |= mask;
    }
    if (g_card_bit_writer_1_index < 0) {
        g_card_bit_writer_1_index = 7;
        g_card_primary_bitstream_cursor++;
    }
}
