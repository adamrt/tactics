#include "psx/types.h"

extern u8 g_menu_controller_input_0[];
extern u8 g_menu_controller_input_1[];

void* world_get_menu_controller_input(s32 player) {
    if (player == 0) {
        return g_menu_controller_input_0;
    }
    return g_menu_controller_input_1;
}
