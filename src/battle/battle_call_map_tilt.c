#include "psx/types.h"

extern s32 g_battle_map_tilt_action;
extern u32 g_controller_input;
extern void battle_toggle_map_tilt(void);

void battle_call_map_tilt(void) {
    if (g_battle_map_tilt_action == 0) {
        if ((g_controller_input & 2) != 0) {
            battle_toggle_map_tilt();
        }
    }
}
