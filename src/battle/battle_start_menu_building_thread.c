#include "psx/types.h"

extern s32 battle_check_thread_running_status(s32 id);
extern s32 battle_is_battle_camera_active(void);
extern void battle_thread_initialize(s32 id, void (*fn)(void));
extern void battle_store_thread_function_parameters(s32 id, s32 a, s32 b, s32 c);
extern void battle_menu_building_thread(void);

extern s32 g_battle_current_menu_id;
extern s32 D_80169200;
extern u16 D_80166050;
extern u16 g_option_menu_open;
extern s32 g_companion_overlay_state;
extern s32 g_help_menu_open;

void battle_start_menu_building_thread(void) {
    if (battle_check_thread_running_status(8) != 0 || battle_check_thread_running_status(3) != 0) {
        if (g_battle_current_menu_id != 10) {
            D_80169200 = 1;
        }
    }
    if (D_80166050 != 0) {
        return;
    }
    if (g_option_menu_open != 0) {
        return;
    }
    if (battle_is_battle_camera_active() != 0) {
        return;
    }
    if (g_companion_overlay_state != 0) {
        return;
    }
    if (battle_check_thread_running_status(3) != 0) {
        return;
    }
    g_help_menu_open = 1;
    battle_thread_initialize(3, battle_menu_building_thread);
    battle_store_thread_function_parameters(3, 0, 0, 0);
}
