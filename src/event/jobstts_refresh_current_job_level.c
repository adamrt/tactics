#include "psx/types.h"

extern s16 g_jobstts_job_ids[];
extern u8* g_jobstts_unit_data[];
extern s32 g_jobstts_current_job_level;
extern s32 jobstts_get_generic_job_index(s32 job_id);

s32 jobstts_refresh_current_job_level(s32 index) {
    s32 generic_job = jobstts_get_generic_job_index(g_jobstts_job_ids[index]);
    u8* unit = g_jobstts_unit_data[0];
    s32 job_level_index = generic_job >> 1;
    u8 packed_levels;

    unit += job_level_index;
    packed_levels = unit[0x44];

    g_jobstts_current_job_level = packed_levels;
    if (generic_job & 1) {
        g_jobstts_current_job_level &= 0xf;
    } else {
        g_jobstts_current_job_level >>= 4;
    }
    return g_jobstts_current_job_level;
}
