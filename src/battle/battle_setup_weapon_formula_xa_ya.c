#include "fft/battle.h"
#include "fft/data.h"

extern battle_stats_t* g_current_attacker;
extern item_data_t g_primary_item_data[];
extern s16 g_current_ability_xa;
extern s16 g_current_ability_ya;
extern u8 g_current_ability_weapon_id;
extern u8 g_current_ability_weapon_power;

void battle_setup_weapon_formula_xa_ya(void) {
    u8 weapon_type = g_primary_item_data[g_current_ability_weapon_id].type;

    if (weapon_type == 0x0f) {
        g_current_ability_xa = g_current_attacker->attributes[0] * 3 / 2;
    } else {
        g_current_ability_xa = g_current_attacker->attributes[0];
    }

    if (weapon_type == 0) {
        s16* ya = &g_current_ability_ya;
        s32 value;

        value = g_current_ability_xa * g_current_attacker->brave / 100;
        *ya = value;
        if ((s16)value == 0) {
            *ya = value + 1;
        }
    } else {
        g_current_ability_ya = g_current_ability_weapon_power;
    }
}
