#include "psx/types.h"

extern u32 g_jobstts_current_job_jp;

u32 jobstts_get_current_job_jp(void) {
    return g_jobstts_current_job_jp;
}
