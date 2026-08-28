#include "psx/types.h"

extern u8 g_card_decreasing_fade_active;
extern u8 g_card_increasing_fade_active;

s32 card_get_fade_state(void) {
    return g_card_decreasing_fade_active + (g_card_increasing_fade_active << 1);
}
