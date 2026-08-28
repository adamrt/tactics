#include "fft/battle.h"
#include "psx/types.h"

extern s32 battle_load_job_level(battle_stats_t* unit, s32 job, s32* jp);
extern void func_8017EA80(u8, u8, s32, s32);
extern u8 g_battle_job_level_gained_flag;

/* Runs the reaction and, if it changed the unit's job level, sets the
   "job level changed" flag so the caller queues the level-up report. */
void battle_main_reaction_subroutine_entd_id_stuff(battle_stats_t* unit) {
    s32 jp;
    s32 initial_level;
    u8 job;
    u8 misc_unit_id;

    job = unit->job_id;
    misc_unit_id = unit->misc_unit_id;
    initial_level = battle_load_job_level(unit, job, &jp);
    func_8017EA80(misc_unit_id, unit->action.jp_change,
        unit->initial_team_flags & BATTLE_TEAM_MASK, jp);
    if (battle_load_job_level(unit, job, &jp) != initial_level) {
        g_battle_job_level_gained_flag = 1;
    }
}
