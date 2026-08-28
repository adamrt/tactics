#include "psx/types.h"

extern s32 g_world_bin_load_request;

void world_request_bin_file_load_8(void) {
    g_world_bin_load_request = 8;
}
