#include "psx/types.h"

extern s32 VSync(s32 mode);
extern s32 g_world_event_random_seed;

void world_seed_event_rng_from_vsync(void) {
    g_world_event_random_seed = VSync(-1);
}
