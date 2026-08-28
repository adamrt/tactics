#include "fft/battle.h"

extern s32 g_battle_game_state;
extern s32 g_help_menu_opening;
extern void battle_stop_game_flow(void);
extern void open_free_cursor_help_menu(void);

void battle_open_mini_menu_help(void) {
    battle_stop_game_flow();
    g_battle_game_state = BATTLE_GAME_STATE_MINI_MENU_HELP;
    g_help_menu_opening = 1;
    open_free_cursor_help_menu();
}
