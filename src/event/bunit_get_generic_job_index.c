#include "psx/types.h"

/* Map generic job IDs (0x4a..0x5d) to zero-based indexes; unique jobs map to 0. */
s16 bunit_get_generic_job_index(s32 job_id) {
    u16 job_index = job_id - (unsigned long long)0x4a;
    s16 result;

    if (job_index < 0x14) {
        result = job_id - 0x4a;
    } else {
        result = 0;
    }
    return result;
}
