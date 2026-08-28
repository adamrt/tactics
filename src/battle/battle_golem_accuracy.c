#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* volatile g_current_attacker;
extern battle_action_data_t* g_target_current_action;
extern u8 g_current_ability_attacker_faith;
extern void battle_store_ma_and_x(void);
extern void battle_apply_magic_attack_up(void);
extern void battle_store_xa_plus_ya_status_damage(void);
extern void use_hp_damage_as_action_hit_percent(void);

s32 battle_golem_accuracy(void) {
    battle_action_data_t* action;

    battle_store_ma_and_x();
    battle_apply_magic_attack_up();
    battle_store_xa_plus_ya_status_damage();
    if ((g_current_attacker->current_status[4] & 0x80) != 0) {
        g_current_ability_attacker_faith = 0x64;
    }
    if ((g_current_attacker->current_status[4] & 0x40) != 0) {
        g_current_ability_attacker_faith = 0;
    }
    action = g_target_current_action;
    /* The target reads hp_damage signed (lh). */
    action->hp_damage = (s16)(*(s16*)&action->hp_damage * g_current_ability_attacker_faith / 100);
    use_hp_damage_as_action_hit_percent();
    return g_target_current_action->hit == 0;
}
