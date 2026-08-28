#include "psx/types.h"

extern u8* func_8005A8A4(s32 a0);

u8 world_get_job_s_skillset(s32 job_id) {
    return *func_8005A8A4(job_id);
}
