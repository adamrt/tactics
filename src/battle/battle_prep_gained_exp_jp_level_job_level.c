#include "fft/battle.h"
#include "psx/types.h"

extern s8 battle_load_job_level(battle_stats_t* unit, u8 job, s32* out);
extern s32 func_8018BE08(u8 job);
extern s32 g_battle_action_type;
extern s32 g_battle_acting_unit_id;
extern u8 D_8019390C;
extern u8 g_battle_job_level_gained_flag;

s32 battle_prep_gained_exp_jp_level_job_level(battle_stats_t* unit, u8* out) {
    s32 sp10[2];
    s32 ret;
    u8* flag;
    s32 job;

    if (unit->entd_slot == 0xFF) {
        return -1;
    }
    job = unit->misc_unit_id;
    flag = &D_8019390C;
    *flag = 0;
    g_battle_job_level_gained_flag = 0;
    g_battle_action_type = 1;
    g_battle_acting_unit_id = job;
    ret = func_8018BE08(unit->misc_unit_id);
    g_battle_action_type = 0;
    out[0] = unit->action.exp_change;
    out[1] = unit->action.jp_change;
    out[2] = 0;
    if (*flag != 0) {
        out[2] = unit->level;
    }
    out[3] = 0;
    if (g_battle_job_level_gained_flag != 0) {
        out[3] = battle_load_job_level(unit, unit->job_id, sp10);
    }
    return ret;
}
