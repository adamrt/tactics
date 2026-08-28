#include "psx/types.h"

extern void set_at_list_active(void);
extern s32 D_80045980;
extern s32 g_battle_game_state;

void battle_half_animation_speed_for_effects(void) {
    D_80045980 = 2;
    g_battle_game_state = 0x33;
    set_at_list_active();
}
