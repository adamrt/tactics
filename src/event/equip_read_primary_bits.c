#include "psx/types.h"

extern u8 g_equip_bit_reader_1_reset;
extern s32 g_equip_bit_reader_1_index;
extern u8* g_equip_bit_reader_1_stream;

s32 equip_read_primary_bits(s32 count) {
    s32 result;
    u8* p;
    s32 bit;
    u8 byte;

    if (count == 0) {
        return 0;
    }
    if (g_equip_bit_reader_1_reset != 0) {
        g_equip_bit_reader_1_index = 7;
        g_equip_bit_reader_1_reset = 0;
    }
    result = 0;
    for (count = count - 1; count != -1; count--) {
        p = g_equip_bit_reader_1_stream;
        byte = *p;
        bit = g_equip_bit_reader_1_index;
        g_equip_bit_reader_1_index = bit - 1;
        if ((byte >> bit) & 1) {
            result |= 1 << count;
        }
        if (g_equip_bit_reader_1_index < 0) {
            g_equip_bit_reader_1_index = 7;
            g_equip_bit_reader_1_stream = p + 1;
        }
    }
    return result;
}
