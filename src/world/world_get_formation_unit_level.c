#include "fft/data.h"

s16 world_get_formation_unit_level(s32 unit_id) {
    return g_world_formation_unit_pointers[unit_id]->level;
}
