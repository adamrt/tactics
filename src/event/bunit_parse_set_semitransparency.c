#include "psx/types.h"

extern s16 g_bunit_semitrans_enabled;

u8* bunit_parse_set_semitransparency(u8* data) {
    g_bunit_semitrans_enabled = data[3];
    return data + data[1];
}
