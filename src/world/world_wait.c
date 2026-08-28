#include "psx/types.h"

void world_switch_to_next_thread(void);

void world_wait(s32 ticks) {
    s32 tick = 0;

    while (tick < ticks) {
        world_switch_to_next_thread();
        tick++;
    }
}
