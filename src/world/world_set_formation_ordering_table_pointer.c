#include "psx/types.h"

extern void* g_world_formation_ordering_table;

void world_set_formation_ordering_table_pointer(void* ordering_table) {
    g_world_formation_ordering_table = ordering_table;
}
