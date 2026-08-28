#include "psx/types.h"

extern s32 main_calculate_job_level(u16 jp);

void main_initialize_unit_s_job_levels(u16* unit_job_jp, u8* unit_job_levels) {
    s32 i;
    u8* job_levels;
    u16* job_jp;
    s32 level;

    i = 0;
    job_levels = unit_job_levels;
    job_jp = unit_job_jp;
    do {
        i += 1;
        level = main_calculate_job_level(job_jp[0]) << 4;
        *job_levels = (u8)(level | main_calculate_job_level(job_jp[1]));
        job_jp += 2;
        job_levels += 1;
    } while (i < 10);
}
