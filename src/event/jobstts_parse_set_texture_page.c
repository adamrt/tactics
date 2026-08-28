#include "psx/gpu.h"

extern u16 g_jobstts_texture_page;

const u8* jobstts_parse_set_texture_page(const u8* data) {
    g_jobstts_texture_page = GetTPage(data[4], data[2] >> 4, data[3] << 4, data[2] << 8);
    return data + data[1];
}
