#include "fft/data.h"
#include "fft/job.h"

s32 world_check_two_swords(s16 unit_id) {
    return g_world_formation_unit_pointers[unit_id]->support_sets_3 & WORLD_SUPPORT_SET_3_TWO_SWORDS;
}
