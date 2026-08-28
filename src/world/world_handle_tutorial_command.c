#include "fft/data.h"

extern u8 D_8018E48C;
extern u8* g_world_tutorial_command_ptr;
extern s32 g_world_tutorial_button_input;
extern s16 g_world_tutorial_wait_timer;
extern s16 D_80193CB2;

extern s32 main_read_controller_input(s32 port);
extern void world_game_reset(void);
extern void func_8012E674(void);
extern void world_handle_tutorial_command_shift(void);
extern void world_handle_tutorial_command_display_message(void);
extern void func_8012E0B8(void);
extern void world_handle_tutorial_command_wait(void);
extern void world_handle_tutorial_command_wait_time(void);
extern void func_8012EB08(void);
extern s32 func_8012DCD4(void);
extern void world_handle_tutorial_command_wait_for_message(void);
extern void world_handle_tutorial_command_change_dialog(void);

/* L1 + R1 + Select + Start (wiki page 00010216) restarts the game. */
#define TUTORIAL_RESET_BUTTONS 0x90C

s32 world_handle_tutorial_command(void) {
    s32 pad;
    u8 cmd;

    if (D_8018E48C == 0) {
        return 1;
    }
    g_world_tutorial_button_input = main_read_controller_input(0);
    if (g_world_tutorial_button_input == TUTORIAL_RESET_BUTTONS) {
        world_game_reset();
    }
    D_80193CB2 = g_world_tutorial_button_input;
    if (g_world_tutorial_wait_timer != 0) {
        func_8012E674();
    }
    cmd = *g_world_tutorial_command_ptr;
    if (cmd < WORLD_TUTORIAL_CMD_SHIFT_LIMIT) {
        world_handle_tutorial_command_shift();
    } else if (cmd == WORLD_TUTORIAL_CMD_DISPLAY_MESSAGE) {
        world_handle_tutorial_command_display_message();
    } else if (cmd == WORLD_TUTORIAL_CMD_DRAW_CIRCLE) {
        func_8012E0B8();
    } else if (cmd == WORLD_TUTORIAL_CMD_WAIT) {
        world_handle_tutorial_command_wait();
    } else if (cmd == WORLD_TUTORIAL_CMD_WAIT_TIME) {
        world_handle_tutorial_command_wait_time();
    } else if (cmd == WORLD_TUTORIAL_CMD_WAIT_FOR_MESSAGE_2) {
        func_8012EB08();
    } else if (cmd == WORLD_TUTORIAL_CMD_END) {
        return func_8012DCD4();
    } else if (cmd == WORLD_TUTORIAL_CMD_WAIT_FOR_MESSAGE) {
        world_handle_tutorial_command_wait_for_message();
    } else if (cmd == WORLD_TUTORIAL_CMD_CHANGE_DIALOG) {
        world_handle_tutorial_command_change_dialog();
    }
    return 1;
}
