#include "psx/types.h"

extern s32 g_jobstts_current_job_level;

s32 jobstts_get_current_job_level(void) {
    return g_jobstts_current_job_level;
}
