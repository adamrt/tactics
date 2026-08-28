#include "psx/types.h"

extern u8* g_job_data_pointer;
extern void main_copy_byte_data(const u8* source, u8* destination, s32 count);

void main_copy_job_growths_and_multipliers_to_unit(u8* unit_data) {
    u8 job_id = unit_data[3];

    main_copy_byte_data(g_job_data_pointer + job_id * 0x30 + 0xd, unit_data + 0x81, 0xa);
}
