#include "fft/battle.h"

extern battle_stats_t* volatile g_current_attacker;
extern s16 g_current_ability_xa;
extern u8 g_current_ability_weapon_characteristics;
extern u8 g_current_ability_two_hands_active;
extern u8 g_current_ability_weapon_id;

void battle_apply_physical_attack_supports(void) {
    u8 weapon_characteristics = g_current_ability_weapon_characteristics;

    if (!(weapon_characteristics & 1) && (weapon_characteristics & 4) && g_current_ability_two_hands_active) {
        g_current_ability_xa *= 2;
    }

    if (g_current_attacker->support_abilities[1] & 0x10) {
        s16* xa = &g_current_ability_xa;

        *xa = *xa * 4 / 3;
    }

    if (g_current_ability_weapon_id == 0 && (g_current_attacker->support_abilities[2] & 0x20)) {
        g_current_ability_xa = g_current_ability_xa * 3 / 2;
    }
}
