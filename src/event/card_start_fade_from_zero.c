#include "psx/types.h"

extern u8 g_card_increasing_fade_active;
extern s16 g_card_fade_intensity;

void card_start_fade_from_zero(void) {
    g_card_increasing_fade_active = 1;
    g_card_fade_intensity = 0;
}
