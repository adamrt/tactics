#include "psx/types.h"

enum {
    RESET_BUTTON_MASK = 0x090c,
};

extern u32 main_read_controller_input(s32 port);
extern void main_game_reset(void);
extern u32 g_controller_input_raw;
extern u32 g_controller_input_previous;
extern u32 g_controller_input_pressed;
extern u32 g_controller_input_released;

s32 battle_update_deployment_controller_input(void) {
    u32 previous;
    u32 current;

    current = main_read_controller_input(1);
    previous = g_controller_input_previous;
    g_controller_input_raw = current;
    g_controller_input_previous = current;
    g_controller_input_pressed = ~previous & current;
    g_controller_input_released = ~current & previous;

    if ((current & RESET_BUTTON_MASK) == RESET_BUTTON_MASK) {
        main_game_reset();
    }
    return 1;
}
