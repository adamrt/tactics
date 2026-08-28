#include "psx/gpu.h"

extern u16 g_card_texture_page;

const u8* card_parse_set_texture_page(const u8* data) {
    g_card_texture_page = GetTPage(data[4], 0, data[3] << 4, data[2] << 8);
    return data + data[1];
}
