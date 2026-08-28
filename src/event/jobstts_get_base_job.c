#include "psx/types.h"

extern u8* g_jobstts_unit_data[];

enum {
    JOBSTTS_BASE_JOB_GENERIC_MONSTER = 0x82,
    JOBSTTS_BASE_JOB_GENERIC_FIRST = 0x80,
    JOBSTTS_JOB_SQUIRE = 0x4a,
};

s32 jobstts_get_base_job(s16 unit_id) {
    u8* unit = g_jobstts_unit_data[unit_id];
    s32 job_id = unit[7];

    if (job_id == JOBSTTS_BASE_JOB_GENERIC_MONSTER) {
        job_id = *(s16*)unit;
    } else if ((u32)job_id >= JOBSTTS_BASE_JOB_GENERIC_FIRST) {
        job_id = JOBSTTS_JOB_SQUIRE;
    }
    return job_id;
}
