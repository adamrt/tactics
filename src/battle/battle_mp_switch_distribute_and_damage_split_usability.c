#include "fft/battle.h"
#include "psx/types.h"

extern u8 g_current_ability_formula;
extern battle_stats_t* g_current_target;
extern s32 battle_check_if_unit_can_react_1(battle_stats_t*);
extern void battle_mp_switch_usability(battle_stats_t*);
extern void battle_distribute_usability(battle_stats_t*);
extern void battle_damage_split_usability(battle_stats_t*);

void battle_mp_switch_distribute_and_damage_split_usability(void) {
    battle_stats_t* unit;
    u8 flags;

    if (g_current_ability_formula == 7)
        return;
    if (battle_check_if_unit_can_react_1(g_current_target) != 0)
        return;
    unit = g_current_target;
    flags = unit->reaction_abilities[2];
    if (flags & 1) {
        battle_mp_switch_usability(unit);
        return;
    }
    if (flags & 2) {
        battle_distribute_usability(unit);
        return;
    }
    if (unit->reaction_abilities[3] & 0x80) {
        battle_damage_split_usability(unit);
    }
}
