#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_crystal_dead_jump_petrify_treasure_check(void);
extern void battle_set_action_target_variables(battle_stats_t* unit);
extern battle_action_data_t* g_target_current_action;

u8 battle_poison_and_regen(battle_stats_t* unit) {
    u8 status;
    if (battle_crystal_dead_jump_petrify_treasure_check() != 0) {
        return 0;
    }
    battle_set_action_target_variables(unit);
    status = unit->current_status[3];
    if (status & 0x80) {
        g_target_current_action->hp_damage = unit->max_hp >> 3;
        g_target_current_action->attack_type = BATTLE_ACTION_TYPE_HP_DAMAGE;
    } else if (status & 0x40) {
        g_target_current_action->hp_healing = unit->max_hp >> 3;
        g_target_current_action->attack_type = BATTLE_ACTION_TYPE_HP_HEALING;
    }
    return g_target_current_action->attack_type;
}
