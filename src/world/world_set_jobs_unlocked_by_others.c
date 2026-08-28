#include "fft/data.h"
#include "fft/job.h"

extern s32 world_special_monster_check(s16 job_id);
extern void world_store_data_pointer_2(u8* ptr);
extern s32 world_bin_check_if_job_is_unlocked(s32 n);

s32 world_set_jobs_unlocked_by_others(s16 job_id) {
    s32 i;

    for (i = 0; i < g_world_formation_unit_count; i++) {
        if (world_special_monster_check(g_world_formation_unit_pointers[i]->job_id) == 0) {
            world_store_data_pointer_2(g_world_formation_unit_pointers[i]->unlocked_jobs);
            world_bin_check_if_job_is_unlocked(job_id - JOB_ID_SQUIRE);
            if (world_bin_check_if_job_is_unlocked(1) != 0) {
                return 0;
            }
        }
    }
    return 1;
}
