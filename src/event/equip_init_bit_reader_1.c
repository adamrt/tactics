#include "psx/types.h"

extern u8 g_equip_bit_reader_1_reset;
extern const u8* g_equip_bit_reader_1_stream;

void equip_init_bit_reader_1(const u8* data) {
    g_equip_bit_reader_1_reset = 1;
    g_equip_bit_reader_1_stream = data;
}
