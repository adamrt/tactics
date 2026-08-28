#include "psx/types.h"

extern s32 func_8005DC14(u8* arg0, s32 arg1);

void world_calculate_and_store_job_unlocks(u8* arg0, u8* arg1) {
    s32 v = func_8005DC14(arg0 + 0x64, arg0[4] & 0xC0);
    arg1[0] = (s8)(v >> 16);
    arg1[1] = (s8)(v >> 8);
    arg1[2] = (s8)v;
}
