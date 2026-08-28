#include "psx/types.h"

extern u32* g_card_render_otag;

void card_set_render_otag(u32* otag) {
    g_card_render_otag = otag;
}
