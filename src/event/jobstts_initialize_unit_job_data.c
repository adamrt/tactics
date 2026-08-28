#include "fft/battle.h"

extern battle_stats_t* get_battle_stats_pointer(s32 unit_id);
extern void jobstts_copy_unit_job_data(battle_stats_t* battle_stats,
    void* destination);
extern u8 g_jobstts_unit_job_data[];
extern u8* g_jobstts_unit_data[];

void jobstts_initialize_unit_job_data(s32 unit_id) {
    jobstts_copy_unit_job_data(get_battle_stats_pointer(unit_id),
        g_jobstts_unit_job_data);
    g_jobstts_unit_data[0] = g_jobstts_unit_job_data;
}
