#include "psx/types.h"

extern s32 battle_get_script_variable(s32 id);

extern u8 D_801938D8;
extern u8 g_current_ability_base_hit;
extern u8 D_80062EBD[];

void battle_weather_effects_on_bows(void) {
    u8* p;
    s32 a;
    s32 b;

    if ((u32)(D_80062EBD[D_801938D8 * 12] - 0xB) < 2) {
        a = battle_get_script_variable(0x23);
        b = battle_get_script_variable(0x24);
        if (b == 1) {
            g_current_ability_base_hit = g_current_ability_base_hit * 3 / 4;
        }
        if ((u32)(a - 3) < 2) {
            p = &g_current_ability_base_hit;
            *p = *p * 3 / 4;
        }
    }
}
