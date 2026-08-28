#include "psx/types.h"

extern s16 g_bunit_job_ids[];
extern s16 g_bunit_selected_unit_index;
extern s32 g_bunit_current_job_mastered;

extern s32 bunit_create_ability_list(
    s32 unit_index, s32 job_id, s32 ability_category, s16* ability_list,
    s32 mode);

s32 bunit_refresh_current_job_mastered(s32 index) {
    g_bunit_current_job_mastered = bunit_create_ability_list(
                                       g_bunit_selected_unit_index, g_bunit_job_ids[index], 15, 0, 3)
        == 0;
    return g_bunit_current_job_mastered;
}
