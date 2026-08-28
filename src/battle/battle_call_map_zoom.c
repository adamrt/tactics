#include "psx/types.h"

extern s32 g_battle_map_zoom_action;
extern u32 g_controller_input;
extern void toggle_map_zoom(void);

void battle_call_map_zoom(void) {
    if (g_battle_map_zoom_action == 0) {
        if ((g_controller_input & 1) != 0) {
            toggle_map_zoom();
        }
    }
}
