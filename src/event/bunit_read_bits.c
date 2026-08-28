#include "psx/types.h"

extern u8 g_bunit_bit_reader_reset;
extern s32 g_bunit_bit_index;
extern const u8* g_bunit_bitstream_cursor;

/*
 * The last three nominal parameters model the caller-saved argument registers
 * reused by the retail routine. Only bit_count is an input; accumulator is
 * initialized before use.
 */
s32 bunit_read_bits(
    s32 bit_count, s32 unused_a1, s32 unused_a2, s32 accumulator) {
    if (bit_count == 0) {
        return 0;
    }

    bit_count &= 0x1f;
    if (g_bunit_bit_reader_reset != 0) {
        g_bunit_bit_index = 7;
        g_bunit_bit_reader_reset = 0;
    }

    bit_count--;
    accumulator = 0;
    if (bit_count != -1) {
        do {
            if (((s32)*g_bunit_bitstream_cursor >> g_bunit_bit_index--) & 1) {
                accumulator |= 1 << bit_count;
            }
            bit_count--;
            if (g_bunit_bit_index < 0) {
                g_bunit_bit_index = 7;
                g_bunit_bitstream_cursor++;
            }
        } while (bit_count != -1);
    }
    return accumulator;
}
