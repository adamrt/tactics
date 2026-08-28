#include "psx/types.h"

extern u8 g_card_text_color[3];

void card_set_text_color(const u8* data) {
    g_card_text_color[0] = data[0];
    g_card_text_color[1] = data[1];
    g_card_text_color[2] = data[2];
}
