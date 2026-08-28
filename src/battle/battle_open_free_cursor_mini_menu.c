#include "fft/battle.h"

extern s32 g_battle_game_state;
extern void battle_stop_game_flow(void);
extern void open_mini_menu_display(void);

void battle_open_free_cursor_mini_menu(void) {
    battle_stop_game_flow();
    g_battle_game_state = BATTLE_GAME_STATE_MINI_MENU;
    open_mini_menu_display();
}
