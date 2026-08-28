#include "psx/types.h"

extern u8 g_card_text_color[3];

u8* card_get_text_color(void) {
    return g_card_text_color;
}
