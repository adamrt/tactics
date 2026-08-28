#include "psx/types.h"

extern u8 g_equip_bit_reader_2_reset;
extern const u8* g_equip_bit_reader_2_stream;

void equip_init_bit_reader_2(const u8* data) {
    g_equip_bit_reader_2_reset = 1;
    g_equip_bit_reader_2_stream = data;
}
