#include "psx/types.h"

s32 wldcore_map_job_id_to_category_index(s32 job_id) {
    if (job_id < 74) {
        return 22;
    }
    if (job_id < 94) {
        return job_id - 74;
    }
    return 21;
}
