#include "fft/bunit.h"
#include "fft/job.h"
#include "psx/types.h"

extern bunit_unit_data_t* g_bunit_unit_data[];

extern s32 bunit_get_base_job(s32 unit_id);
extern s32 bunit_is_special_monster_job(s32 job_id);
extern void bunit_init_bit_reader(const u8* unit_job_data);
extern s32 bunit_read_bits(s32 count);

s32 bunit_calculate_unit_jobs(s32 unit_id, s16* job_ids) {
    s32 saved_unit_id = unit_id;
    u32 unit_index = (u8)saved_unit_id;
    bunit_unit_data_t** unit_table = g_bunit_unit_data;
    void* working_pointer;
    s16* job_ids_output;
    bunit_unit_data_t* unit_data;
    bunit_unit_data_t** unit_data_cursor;
    s32 job_count;
    s32 generic_job_index;

    working_pointer = (u8*)unit_table + unit_index * 4;
    unit_data = *(bunit_unit_data_t**)working_pointer;
    job_ids_output = job_ids;
    bunit_init_bit_reader(&unit_data->job_id + 1);
    job_ids_output[0] = bunit_get_base_job(saved_unit_id & 0xff);
    job_count = 1;
    if (bunit_is_special_monster_job(
            (*(bunit_unit_data_t**)working_pointer)->monster_base_job_id)
        || *(s16*)((u8*)*(bunit_unit_data_t**)working_pointer + 0x3e) != 0) {
        job_ids_output[1] = -1;
        return 1;
    }

    bunit_read_bits(1);
    generic_job_index = 1;
    unit_data_cursor = (bunit_unit_data_t**)working_pointer;
    working_pointer = job_ids_output + 1;
    for (; generic_job_index < 0x14; generic_job_index++) {
        s32 job_is_unlocked;

        job_is_unlocked = bunit_read_bits(1);
        saved_unit_id = generic_job_index + JOB_ID_SQUIRE;
        if (saved_unit_id == 0x5b && (*(u8*)((u8*)*unit_data_cursor + 0x70) & 0x40) != 0) {
            continue;
        }
        if (saved_unit_id == 0x5c && (*(u8*)((u8*)*unit_data_cursor + 0x70) & 0x80) != 0) {
            continue;
        }
        if (job_is_unlocked != 0) {
            *(s16*)working_pointer = saved_unit_id;
            working_pointer = (s16*)working_pointer + 1;
            job_count++;
        }
    }
    job_ids_output[job_count] = -1;
    return job_count;
}
