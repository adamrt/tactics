#include "psx/types.h"

extern void* g_world_bin_load_request;
extern void* D_801532EC;
extern u16 D_801CD50C;

extern void world_switch_to_next_thread(void);
extern void world_stop_current_thread(void);

void world_bin_load_file(void* request) {
    while (g_world_bin_load_request != 0 || D_801532EC != 0) {
        world_switch_to_next_thread();
    }
    g_world_bin_load_request = request;
    while (g_world_bin_load_request != 0) {
        world_switch_to_next_thread();
    }
    if (D_801CD50C == 1) {
        world_stop_current_thread();
    }
}
