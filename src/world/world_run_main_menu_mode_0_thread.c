#include "psx/types.h"

extern void world_run_main_menu_mode(s32 mode);

void world_run_main_menu_mode_0_thread(void) {
    world_run_main_menu_mode(0);
}
