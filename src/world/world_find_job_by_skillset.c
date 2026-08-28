#include "psx/types.h"

extern u8* main_get_job_data_pointer(s32 job);

s32 world_find_job_by_skillset(s32 skillset) {
    s32 i;

    for (i = 0; i < 0xA0; i++) {
        if (*main_get_job_data_pointer(i) == skillset) {
            return i;
        }
    }
    return -1;
}
