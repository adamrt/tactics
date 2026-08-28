#include "psx/types.h"

extern u32 g_bunit_current_job_jp;

u32 bunit_get_current_job_jp(void) {
    return g_bunit_current_job_jp;
}
