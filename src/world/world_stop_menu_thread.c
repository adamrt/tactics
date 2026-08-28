#include "psx/types.h"

extern s32 g_world_menu_thread_running_status;
extern void world_bin_turn_off_unit_status_banner_thread(s32 thread_id);

void world_stop_menu_thread(s32 thread_id) {
    world_bin_turn_off_unit_status_banner_thread(thread_id);
    g_world_menu_thread_running_status = 0;
}
