#include "psx/types.h"

extern s32 g_jobstts_current_job_mastered;

s32 jobstts_is_current_job_mastered(void) {
    return g_jobstts_current_job_mastered;
}
