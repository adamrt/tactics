#include "psx/types.h"

void main_store_job_unlock_bitset(u8 destination[3], u32 unlocked_jobs) {
    *destination++ = unlocked_jobs >> 16;
    *destination++ = unlocked_jobs >> 8;
    *destination = unlocked_jobs;
}
