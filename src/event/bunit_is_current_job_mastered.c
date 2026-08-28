#include "psx/types.h"

extern s32 g_bunit_current_job_mastered;

s32 bunit_is_current_job_mastered(void) {
    return g_bunit_current_job_mastered;
}
