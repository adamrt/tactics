#include "psx/types.h"

extern u8 g_world_should_reset_bit_read;
extern u8* g_world_stored_bit_pointer;

void world_store_combined_bit_value_pointer(u8* ptr) {
    g_world_should_reset_bit_read = 1;
    g_world_stored_bit_pointer = ptr;
}
