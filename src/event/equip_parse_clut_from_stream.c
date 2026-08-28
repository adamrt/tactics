#include "psx/gpu.h"

extern u16 g_equip_clut_id;

const u8* equip_parse_clut_from_stream(const u8* data) {
    g_equip_clut_id = GetClut(data[3] << 4, data[4] | (data[2] << 8));
    return data + data[1];
}
