#include "fft/data.h"
#include "psx/types.h"

extern job_data_t* main_get_job_data_pointer(s32 job_id);

u8 bunit_get_job_skillset(s32 job_id) {
    return main_get_job_data_pointer(job_id)->skillset;
}
