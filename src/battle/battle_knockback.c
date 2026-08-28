#include "fft/battle.h"
#include "psx/types.h"

extern void battle_action_data_nulling(void);
extern u8 g_current_ability_knockback_flags;
extern u8 D_801938EE;
extern battle_action_data_t* g_target_current_action;
extern battle_stats_t* g_target_unit_data;

void battle_knockback(void) {
    u8* flags;
    battle_stats_t* unit;
    battle_action_data_t* action;
    s32 amount;
    s32 diff;

    battle_action_data_nulling();
    flags = &g_current_ability_knockback_flags;
    *flags &= 0x7F;
    g_target_current_action->attack_type = 1;
    unit = g_target_unit_data;
    amount = 0;
    if ((*(u16*)&unit->current_status[0] & 0x8060) == 0) {
        if (*flags == 1) {
            diff = (D_801938EE >> 1) - unit->jump;
            if (diff > 0) {
                amount = (diff * unit->max_hp) / 10;
                if (amount >= 0x3E8) {
                    amount = 0x3E7;
                }
            }
        }
        action = g_target_current_action;
        action->hp_damage = amount;
        if (amount != 0) {
            action->attack_type |= BATTLE_ACTION_TYPE_HP_DAMAGE;
        }
    }
}
