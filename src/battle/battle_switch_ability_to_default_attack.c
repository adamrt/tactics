#include "fft/battle.h"
#include "psx/types.h"

extern battle_stats_t* volatile g_current_attacker;
extern u8 g_current_ability_target_id;
extern u8 D_801938C3;
extern s16 g_current_ability_reaction_id;
extern s16 g_current_ability_elemental_flags;

extern void func_8018B34C(u8* arg, u8 skillset);

void battle_switch_ability_to_default_attack(void) {
    battle_stats_t* unit;
    battle_stats_t* u2;
    battle_stats_t* u3;
    u8* pc3;
    u8 saved_c3;
    u8 saved_skillset;
    u16 saved_ability;

    unit = g_current_attacker;
    pc3 = &D_801938C3;
    saved_c3 = *pc3;
    saved_skillset = unit->last_skillset_id;
    unit->last_skillset_id = 1;
    u2 = g_current_attacker;
    saved_ability = *(u16*)&unit->last_ability_id;
    *(u16*)&u2->last_ability_id = 0;
    func_8018B34C(&u2->action_actor_id, g_current_ability_target_id);
    u3 = g_current_attacker;
    *pc3 = saved_c3;
    *(u16*)&u3->last_ability_id = saved_ability;
    u3->last_skillset_id = saved_skillset;
    g_current_ability_elemental_flags = 0;
    g_current_ability_reaction_id = 0;
}
