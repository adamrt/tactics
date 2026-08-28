#include "psx/types.h"

extern s32 g_bunit_current_job_level;

s32 bunit_get_current_job_level(void) {
    return g_bunit_current_job_level;
}
