#include "psx/types.h"

extern u8 g_bunit_decreasing_fade_active;
extern s16 g_bunit_fade_intensity;

void bunit_start_fade_from_0xf0(void) {
    g_bunit_decreasing_fade_active = 1;
    g_bunit_fade_intensity = 0xf0;
}
