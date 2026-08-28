#include "psx/types.h"

extern u32 g_jobstts_next_job_level_jp_requirement;

u32 jobstts_get_next_job_level_jp_requirement(void) {
    return g_jobstts_next_job_level_jp_requirement;
}
