#include "fft/battle.h"
#include "psx/types.h"

extern s32 g_battle_acting_unit_id;
extern s32 g_battle_action_type;
extern s32 g_current_ability_hamedo_flag;
extern u16 g_battle_acting_unit_used_ability_id;

extern battle_stats_t battle_stats[];

extern void store_some_acting_unit_data(battle_stats_t*);
extern s32 func_8017DA20(battle_stats_t*);
extern void func_8017D4A0(battle_stats_t*);
extern void battle_current_action_attacker_data_setting(battle_stats_t*);

s32 battle_prep_current_action_data(s32 id) {
    battle_stats_t* unit;
    s32 i;
    battle_stats_t* base;
    s32 r;
    u16 ability;

    g_battle_acting_unit_id = -1;
    g_battle_action_type = 0;
    if (id >= 0x15 || (unit = &battle_stats[id], base = battle_stats, unit->entd_slot == 0xFF)) {
        return -1;
    }
    if (g_current_ability_hamedo_flag != 0) {
        store_some_acting_unit_data(unit);
        return 6;
    }
    r = func_8017DA20(unit);
    if (r != 0) {
        store_some_acting_unit_data(unit);
        return r;
    }
    /* The target loads the s16 last_ability_id unsigned (lhu). */
    ability = *(u16*)&unit->last_ability_id;
    g_battle_acting_unit_id = id;
    g_battle_acting_unit_used_ability_id = ability;
    for (i = 0; i < 0x15; i++) {
        base[i].action.reaction_id = 0;
        base[i].ability_outcome = 0;
    }
    func_8017D4A0(unit);
    battle_current_action_attacker_data_setting(unit);
    return 0;
}
