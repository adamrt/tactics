#include "psx/types.h"

extern u8* g_job_data_pointer;
extern u8 g_status_sets[];
extern void main_copy_byte_data(const u8* source, u8* destination, s32 count);

void main_transfer_job_s_data_to_unit_s_data(u8* unit) {
    u8* job;
    s32 i;
    s32 flag_a;
    s32 flag_b;

    if (unit[0] < 0x4a) {
        unit[0x162] = g_job_data_pointer[unit[0] * 0x30];
    } else {
        unit[0x162] = 0;
    }

    job = g_job_data_pointer + unit[3] * 0x30;
    unit[0x12] = job[0];
    main_copy_byte_data(job + 1, unit + 0xa, 8);
    main_copy_byte_data(job + 9, unit + 0x4a, 4);
    main_copy_byte_data(job + 0xd, unit + 0x81, 0xa);
    unit[0x3a] = job[0x17];
    unit[0x3b] = job[0x18] & 0x7f;
    if (job[0x18] & 0x80) {
        *(u16*)(unit + 0x48) |= 0x4000;
    } else {
        *(u16*)(unit + 0x48) &= 0xbfff;
    }
    main_copy_byte_data(job + 0x1a, unit + 0x4e, 0xf);

    flag_a = unit[5] & 4;
    flag_b = unit[6] & 9;
    if (flag_a != 0 && flag_b != 0) {
        u8* statuses;
        i = 0;
        statuses = unit + 0x53;
        for (; i < 5; i++) {
            if (flag_a != 0) {
                *statuses |= g_status_sets[0x19 + i];
            }
            if (flag_b != 0) {
                *statuses |= g_status_sets[0x1e + i];
            }
            statuses++;
        }
    }

    main_copy_byte_data(job + 0x29, unit + 0x6d, 4);
    unit[0x71] = 0;
    unit[0x15f] = job[0x2d];
    unit[0x160] = job[0x2e];
    unit[0x15e] = job[0x2f];
}
