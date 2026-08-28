#include "psx/types.h"

extern void world_store_menu_input_state(void*);
extern void world_stop_current_thread(void);
extern s16 D_8016E45C;
extern s32 g_world_formation_menu_input_state;

void world_bin_open_formation(void) {
    D_8016E45C = 1;
    g_world_formation_menu_input_state = 0;
    world_store_menu_input_state(&g_world_formation_menu_input_state);
    world_stop_current_thread();
}
