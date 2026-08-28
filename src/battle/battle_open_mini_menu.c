#include "fft/battle.h"

extern s32 g_battle_game_state;
extern void battle_stop_game_flow(void);
extern void set_targeting_tile_background(s32, s32);
extern void enable_mini_menu_display(void);

void battle_open_mini_menu(void) {
    battle_stop_game_flow();
    g_battle_game_state = BATTLE_GAME_STATE_MINI_MENU;
    set_targeting_tile_background(0, 3);
    enable_mini_menu_display();
}
