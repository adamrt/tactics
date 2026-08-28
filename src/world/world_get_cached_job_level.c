#include "psx/types.h"

extern s32 g_world_cached_job_level;

s32 world_get_cached_job_level(void) {
    return g_world_cached_job_level;
}
