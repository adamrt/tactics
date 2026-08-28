#include "psx/types.h"

extern u8 g_world_should_reset_data_read;
extern u8* g_world_stored_data_pointer_2;

void world_store_data_pointer_2(u8* ptr) {
    g_world_should_reset_data_read = 1;
    g_world_stored_data_pointer_2 = ptr;
}
