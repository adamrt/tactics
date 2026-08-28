#include "fft/data.h"
#include "psx/types.h"

extern job_data_t* g_job_data_pointer;

s32 main_find_skillset_job_id(s32 skillset_id) {
    s32 job_id;
    s32 result;
    job_data_t* job_data;

    job_id = 0;
    job_data = g_job_data_pointer;
    skillset_id &= 0xff;

    do {
        s32 checked_job_id = job_id & 0xff;

        if (job_data[checked_job_id].skillset == skillset_id) {
            result = checked_job_id;
            break;
        }
        job_id++;
        result = (u32)(job_id & 0xff) < 0x9f;
    } while (result != 0);
    return result;
}
