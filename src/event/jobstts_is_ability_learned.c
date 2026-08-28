#include "psx/types.h"

extern u16 g_jobstts_ability_entries[];

s32 jobstts_is_ability_learned(s32 index) {
    return ((g_jobstts_ability_entries[index] >> 14) ^ 1) & 1;
}
