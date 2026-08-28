#include "fft/data.h"

s32 world_get_formation_unit_field_120_shr_4_minus_low_nibble(s32 unit_id) {
    world_formation_unit_t* unit = g_world_formation_unit_pointers[unit_id];
    s32 low = unit->unk_120 & 0xF;
    /* Fence: the target reloads unk_120 instead of reusing the first lhu,
     * and keeps the load-delay nop after it. */
    __asm__ __volatile__("");
    return (unit->unk_120 >> 4) - low;
}
