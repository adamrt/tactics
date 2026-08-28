#include "psx/types.h"

extern s16 g_jobstts_job_ids[];
extern s32 g_jobstts_current_job_mastered;
extern s32 jobstts_build_ability_list(s32 fallback_job, s32 base_job,
    s32 ability_category, s16* ability_list,
    s32 mode);

s32 jobstts_refresh_current_job_mastered(s32 index) {
    s16 ability_list[24];

    g_jobstts_current_job_mastered = jobstts_build_ability_list(0, g_jobstts_job_ids[index], 15,
                                         ability_list, 2)
        == 0;
    return g_jobstts_current_job_mastered;
}
