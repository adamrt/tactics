#include "psx/types.h"

extern s16 g_card_text_otag_index;

const u8* card_parse_set_text_otag_index(const u8* data) {
    g_card_text_otag_index = data[3];
    return data + data[1];
}
