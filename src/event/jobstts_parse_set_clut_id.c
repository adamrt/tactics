#include "psx/gpu.h"

extern u16 g_jobstts_clut_id;

const u8* jobstts_parse_set_clut_id(const u8* data) {
    g_jobstts_clut_id = GetClut(data[3] << 4, data[4] | (data[2] << 8));
    return data + data[1];
}
