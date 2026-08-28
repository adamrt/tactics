#include "psx/types.h"

extern u32 g_bunit_next_job_level_jp_requirement;

u32 bunit_get_next_job_level_jp_requirement(void) {
    return g_bunit_next_job_level_jp_requirement;
}
