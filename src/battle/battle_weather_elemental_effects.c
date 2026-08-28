#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_current_ability_element;
extern u8* g_target_current_action;
extern s32 func_8018E660(void);

void battle_weather_elemental_effects(void) {
    u8 element;
    s32 weather;

    element = g_current_ability_element;
    weather = func_8018E660();
    if (weather == 3 || weather == 4) {
        if (element & BATTLE_ELEMENT_FIRE) {
            *(s16*)(g_target_current_action + 4) = *(s16*)(g_target_current_action + 4) * 3 / 4;
        }
        if (element & BATTLE_ELEMENT_LIGHTNING) {
            *(s16*)(g_target_current_action + 4) = *(s16*)(g_target_current_action + 4) * 5 / 4;
        }
    }
    if (weather == 6 || weather == 7) {
        if (element & BATTLE_ELEMENT_ICE) {
            *(s16*)(g_target_current_action + 4) = *(s16*)(g_target_current_action + 4) * 5 / 4;
        }
    }
}
