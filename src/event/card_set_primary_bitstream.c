#include "psx/types.h"

extern u8 g_card_primary_bitstream_reset;
extern const u8* g_card_primary_bitstream_cursor;

void card_set_primary_bitstream(const u8* data) {
    g_card_primary_bitstream_reset = 1;
    g_card_primary_bitstream_cursor = data;
}
