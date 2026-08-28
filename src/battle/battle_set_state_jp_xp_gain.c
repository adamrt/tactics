#include "fft/battle.h"

extern s32 g_animation_speed;
extern s32 g_battle_game_state;
extern u8* get_acting_unit_misc_data(void);

void battle_set_state_jp_xp_gain(void) {
    u8* unit;

    g_animation_speed = 1;
    g_battle_game_state = BATTLE_GAME_STATE_JP_EXP_GAIN;
    unit = get_acting_unit_misc_data();
    if (unit != 0) {
        *(u16*)(unit + 8) = 0;
    }
}
