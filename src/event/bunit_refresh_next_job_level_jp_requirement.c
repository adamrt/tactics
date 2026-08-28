#include "psx/types.h"

extern s16 g_bunit_job_ids[];
extern s32 g_bunit_current_job_level;
extern u32 g_bunit_next_job_level_jp_requirement;
extern const u16 g_job_level_jp_requirements[];

extern s32 bunit_get_generic_job_index(s32 job_id);

u32 bunit_refresh_next_job_level_jp_requirement(s32 index) {
    s32 level;

    bunit_get_generic_job_index(g_bunit_job_ids[index]);
    level = g_bunit_current_job_level & 0xf;
    if (level >= 8) {
        g_bunit_next_job_level_jp_requirement |= 0x20000000;
    } else {
        g_bunit_next_job_level_jp_requirement = g_job_level_jp_requirements[level];
    }
    return g_bunit_next_job_level_jp_requirement;
}
