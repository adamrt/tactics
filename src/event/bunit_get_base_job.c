#include "fft/bunit.h"
#include "fft/job.h"
#include "psx/types.h"

extern bunit_unit_data_t* g_bunit_unit_data[];

enum {
    BUNIT_BASE_JOB_GENERIC_MONSTER = 0x82,
    BUNIT_BASE_JOB_GENERIC_FIRST = 0x80,
};

s32 bunit_get_base_job(s16 unit_id) {
    bunit_unit_data_t* unit = g_bunit_unit_data[unit_id];
    s32 job_id = unit->job_id;

    if (job_id == BUNIT_BASE_JOB_GENERIC_MONSTER) {
        job_id = unit->monster_base_job_id;
    } else if ((u32)job_id >= BUNIT_BASE_JOB_GENERIC_FIRST) {
        job_id = JOB_ID_SQUIRE;
    }
    return job_id;
}
