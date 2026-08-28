#include "psx/types.h"

extern void* battle_get_casting_unit_misc_data(void);
extern void battle_system_function_setup_routine(s32 a, u8 b, u8 c, s32 d, s32 e);
extern s32 g_battle_game_state;
extern s32 g_animation_speed;
extern s32 g_post_effect_msg_counter;
extern u8 D_80096248;
extern u8 D_80096249;
extern s32 D_8009624C;
extern s32 g_post_action;

s32 battle_resume_attack_phase_control(void) {
    s32 idx;
    s32 off;

    g_battle_game_state = 0x2F;
    g_animation_speed = 1;
    battle_get_casting_unit_misc_data();
    idx = g_post_effect_msg_counter;
    if (idx != 0) {
        idx -= 1;
        g_post_effect_msg_counter = idx;
        off = idx * 8;
        battle_system_function_setup_routine(0x11,
            *(u8*)((u8*)&D_80096248 + off),
            *(u8*)((u8*)&D_80096249 + off),
            *(s32*)((u8*)&D_8009624C + off),
            1);
        g_post_action = 0;
        return 1;
    }
    return 0;
}
