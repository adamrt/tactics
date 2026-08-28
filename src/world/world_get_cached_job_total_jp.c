#include "psx/types.h"

extern s32 g_world_cached_job_total_jp;

s32 world_get_cached_job_total_jp(void) {
    return g_world_cached_job_total_jp;
}
