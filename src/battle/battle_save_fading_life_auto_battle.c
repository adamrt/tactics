#include "fft/battle.h"

extern void func_8019490C(u8 x);
extern s32 func_8019619C(void);
extern s32 func_80198B04(void);
extern battle_stats_t* g_temp_unit_data;

s32 battle_save_fading_life_auto_battle(void) {
    if (*(u8*)0x801A0D7B == 0) {
        if (func_80198B04() != 0) {
            *(s8*)0x801A0D7A = 0xE;
            return -2;
        }
        func_8019490C(g_temp_unit_data->auto_battle_target);
    }
    return -(~func_8019619C() == 0);
}
