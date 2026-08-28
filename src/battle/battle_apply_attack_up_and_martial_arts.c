#include "fft/battle.h"
#include "fft/data.h"

extern battle_stats_t* volatile g_current_attacker;
extern item_data_t g_primary_item_data[];
extern s16 g_current_ability_xa;
extern u8 g_current_ability_weapon_id;

void battle_apply_attack_up_and_martial_arts(void) {
    if (g_current_attacker->support_abilities[1] & 0x10) {
        s16* xa = &g_current_ability_xa;

        *xa = *xa * 4 / 3;
    }

    {
        u8 weapon_id = g_current_ability_weapon_id;
        battle_stats_t* attacker = g_current_attacker;
        u8 weapon_type = g_primary_item_data[weapon_id].type;
        u8 has_martial_arts = attacker->support_abilities[2] & 0x20;

        if (has_martial_arts && weapon_type == 0) {
            g_current_ability_xa = g_current_ability_xa * 3 / 2;
        }
    }
}
