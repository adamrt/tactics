#include "fft/data.h"
#include "fft/job.h"

s16 world_get_base_job(s16 formation_idx) {
    world_formation_unit_t* unit = g_world_formation_unit_pointers[formation_idx];
    u32 job = unit->sprite_set;
    if (job == WORLD_SPRITE_SET_MONSTER) {
        job = unit->job_id;
    } else if (job >= WORLD_SPRITE_SET_GENERIC_FIRST) {
        job = JOB_ID_SQUIRE;
    }
    return (s16)job;
}
