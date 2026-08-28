#include "fft/data.h"

s32 world_get_formation_unit_field_120_shr_4(s32 unit_id) {
    return g_world_formation_unit_pointers[unit_id]->unk_120 >> 4;
}
