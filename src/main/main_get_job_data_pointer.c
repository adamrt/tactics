#include "fft/data.h"
#include "fft/job.h"

extern job_data_t g_job_data[];

job_data_t* main_get_job_data_pointer(s32 job_id) {
    if (job_id < JOB_ID_COUNT) {
        return &g_job_data[job_id];
    }
    return 0;
}
