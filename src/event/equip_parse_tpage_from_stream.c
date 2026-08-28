#include "psx/gpu.h"

extern u16 g_equip_texture_page;

const u8* equip_parse_tpage_from_stream(const u8* data) {
    g_equip_texture_page = GetTPage(data[4], data[2] >> 4, data[3] << 4, data[2] << 8);
    return data + data[1];
}
