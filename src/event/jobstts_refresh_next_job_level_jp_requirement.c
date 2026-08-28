#include "psx/types.h"

extern s16 g_jobstts_job_ids[];
extern s32 g_jobstts_current_job_level;
extern s32 g_jobstts_next_job_level_jp_requirement;
extern u16 g_job_level_jp_requirements[];
extern s32 jobstts_get_generic_job_index(s32 job_id);

s32 jobstts_refresh_next_job_level_jp_requirement(s32 index) {
    s32 level;

    jobstts_get_generic_job_index(g_jobstts_job_ids[index]);
    level = g_jobstts_current_job_level & 0xf;
    if (level >= 8) {
        g_jobstts_next_job_level_jp_requirement |= 0x20000000;
    } else {
        g_jobstts_next_job_level_jp_requirement = g_job_level_jp_requirements[level];
    }
    return g_jobstts_next_job_level_jp_requirement;
}
