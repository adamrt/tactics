#include "psx/types.h"

extern s32 g_map_data_load_complete;

/* Mark the asynchronous map-data sequence ready for its next init stage. */
void battle_mark_map_data_load_complete(void) {
    g_map_data_load_complete = 1;
}
