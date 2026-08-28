#include "fft/bunit.h"
#include "fft/job.h"
#include "psx/types.h"

void bunit_store_job_unlocks(bunit_unit_data_t* unit, u8* job_unlocks) {
    s32 unlocks = main_calculate_unlocked_jobs(
        unit->job_levels,
        unit->gender_flags & (UNIT_GENDER_FEMALE | UNIT_GENDER_MALE));

    job_unlocks[0] = unlocks >> 16;
    job_unlocks[1] = unlocks >> 8;
    job_unlocks[2] = unlocks;
}
