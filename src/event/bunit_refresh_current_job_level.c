#include "psx/types.h"

extern s16 g_bunit_job_ids[];
extern s16 g_bunit_selected_unit_index;
extern u8* g_bunit_unit_data[];
extern s32 g_bunit_current_job_level;

extern s32 bunit_get_generic_job_index(s32 job_id);

s32 bunit_refresh_current_job_level(s32 index) {
    s32 generic_job;
    u8* unit;
    s32 job_level_index;
    u8 packed_levels;

    generic_job = bunit_get_generic_job_index(g_bunit_job_ids[index]);
    unit = g_bunit_unit_data[g_bunit_selected_unit_index];
    job_level_index = generic_job >> 1;
    unit += job_level_index;
    packed_levels = unit[0xb1];

    g_bunit_current_job_level = packed_levels;
    if ((generic_job & 1) != 0) {
        g_bunit_current_job_level &= 0xf;
    } else {
        g_bunit_current_job_level >>= 4;
    }
    return g_bunit_current_job_level;
}
