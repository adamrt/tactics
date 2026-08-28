#include "fft/data.h"
#include "fft/job.h"
#include "psx/types.h"

extern job_data_t* main_get_job_data_pointer(s32 job_id);

s32 bunit_find_first_job_for_skillset(s32 skillset_id) {
    s32 job_id = 0;

    do {
        if (main_get_job_data_pointer(job_id)->skillset == skillset_id) {
            return job_id;
        }
        job_id++;
    } while (job_id < JOB_ID_COUNT);

    return -1;
}
