#include "psx/types.h"

extern s16 g_bunit_job_ids[];
extern s16 g_bunit_selected_unit_index;
extern u8* g_bunit_unit_data[];
extern u32 g_bunit_current_job_total_jp;

extern s32 bunit_get_generic_job_index(s32 job_id);

void bunit_refresh_current_job_total_jp(s32 index) {
    s32 generic_job;
    u8* unit;

    generic_job = bunit_get_generic_job_index(g_bunit_job_ids[index]);
    unit = g_bunit_unit_data[g_bunit_selected_unit_index];
    g_bunit_current_job_total_jp = *(u16*)(unit + 0xe4 + generic_job * 2);
}
