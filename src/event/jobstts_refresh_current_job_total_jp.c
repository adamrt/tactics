#include "psx/types.h"

extern s16 g_jobstts_job_ids[];
extern u8* g_jobstts_unit_data[];
extern u32 g_jobstts_current_job_total_jp;
extern s32 jobstts_get_generic_job_index(s32 job_id);

void jobstts_refresh_current_job_total_jp(s32 index) {
    s32 generic_job = jobstts_get_generic_job_index(g_jobstts_job_ids[index]);

    g_jobstts_current_job_total_jp = *(u16*)(g_jobstts_unit_data[0] + 0x76 + generic_job * 2);
}
