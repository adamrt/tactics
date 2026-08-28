typedef signed int s32;

extern s32 g_world_menu_result;

void wldcore_set_menu_result_pending_80092420(void) {
    g_world_menu_result = -1;
}
