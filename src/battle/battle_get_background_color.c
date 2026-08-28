#include "psx/types.h"

extern u8 g_battle_background_color[];

u8* battle_get_background_color(void) {
    return g_battle_background_color;
}
