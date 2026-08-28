#include "psx/types.h"

extern u8 g_world_fade_disabled;

/* When set, the screen fade helpers at 0x8012d418-0x8012d6c8 all bail out
 * immediately, leaving the fade level at 0x801da760 untouched. */
void world_set_fade_disabled(u8 disabled) {
    g_world_fade_disabled = disabled;
}
