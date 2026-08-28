#include "psx/types.h"

extern void* g_world_gs_out_packet_p;

/* Sets the base of the packet work area used by the world GS packet
 * allocator (see world_gs_sortboxfill / func_800E03EC). */
void world_gs_setworkbase(void* base) {
    g_world_gs_out_packet_p = base;
}
