#include "psx/types.h"

extern u8 g_world_should_reset_bit_read;
extern s32 g_world_bit_read_shift;
extern u8* g_world_stored_bit_pointer;

s32 world_get_combined_bit_value_from_stored_pointer(s32 n) {
    s32 result;
    s32 shift;
    s32 c;
    u8* p;

    if (n == 0) {
        return 0;
    }
    result = 0;
    if (g_world_should_reset_bit_read != 0) {
        g_world_bit_read_shift = 7;
        g_world_should_reset_bit_read = 0;
    }
    n -= 1;
    while (n != -1) {
        p = g_world_stored_bit_pointer;
        c = *p;
        shift = g_world_bit_read_shift;
        g_world_bit_read_shift = shift - 1;
        if ((c >> shift) & 1) {
            result |= 1 << n;
        }
        n -= 1;
        if (g_world_bit_read_shift < 0) {
            g_world_bit_read_shift = 7;
            g_world_stored_bit_pointer = p + 1;
        }
    }
    return result;
}
