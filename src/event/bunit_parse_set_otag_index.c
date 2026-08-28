#include "psx/types.h"

extern s16 g_bunit_otag_index;

u8* bunit_parse_set_otag_index(u8* data) {
    g_bunit_otag_index = data[3];
    return data + data[1];
}
