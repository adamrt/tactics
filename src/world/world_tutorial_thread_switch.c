#include "psx/types.h"

extern s32 g_world_tutorial_thread_switch_counter;
void world_switch_to_next_thread(void);

void world_tutorial_thread_switch(void) {
    g_world_tutorial_thread_switch_counter = 0xff;
    do {
        world_switch_to_next_thread();
        g_world_tutorial_thread_switch_counter -= 4;
    } while (g_world_tutorial_thread_switch_counter > 0);
    g_world_tutorial_thread_switch_counter = 0;
}
