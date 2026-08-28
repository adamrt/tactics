#include "psx/gpu.h"

extern u16 g_bunit_texture_page;

/* BUNIT.OUT 001c95c8 - Compute the TPage id from a stream command and cache it,
 * returning the next command pointer. */
const u8* bunit_parse_tpage_from_stream(const u8* data) {
    g_bunit_texture_page = GetTPage(data[4], data[2] >> 4, data[3] << 4, data[2] << 8);
    return data + data[1];
}
