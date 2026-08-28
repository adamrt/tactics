typedef signed int s32;

extern s32 g_world_menu_result;

void wldcore_set_menu_result_pending_8008a454(void) {
    g_world_menu_result = -1;
}
