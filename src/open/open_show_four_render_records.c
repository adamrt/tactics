#include "fft/opening.h"

/* The birthday-menu controller record: four render record indices at
 * offsets 4 through 16. */
typedef struct OpenFourRenderRecordIndices {
    s32 unused;
    s32 indices[4];
} OpenFourRenderRecordIndices;

void open_show_four_render_records(const OpenFourRenderRecordIndices* group) {
    g_open_render_records_36[group->indices[0]].flags |= OPEN_RENDER_RECORD_VISIBLE;
    g_open_render_records_36[group->indices[1]].flags |= OPEN_RENDER_RECORD_VISIBLE;
    g_open_render_records_36[group->indices[2]].flags |= OPEN_RENDER_RECORD_VISIBLE;
    g_open_render_records_36[group->indices[3]].flags |= OPEN_RENDER_RECORD_VISIBLE;
}
