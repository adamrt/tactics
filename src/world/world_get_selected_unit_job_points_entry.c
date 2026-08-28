#include "fft/data.h"

extern s16 g_world_selected_formation_unit_index;
extern s16 D_801C8564;

u16 world_get_selected_unit_job_points_entry(void) {
    return g_world_formation_unit_pointers[g_world_selected_formation_unit_index]->job_points[D_801C8564];
}
