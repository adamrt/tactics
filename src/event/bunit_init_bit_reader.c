#include "psx/types.h"

extern u8 g_bunit_bit_reader_reset;
extern const u8* g_bunit_bitstream_cursor;

void bunit_init_bit_reader(const u8* data) {
    g_bunit_bit_reader_reset = 1;
    g_bunit_bitstream_cursor = data;
}
