#include "psx/types.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;
#define setaddr(p, a) (((P_TAG*)(p))->addr = (u32)(a))
#define getaddr(p)    ((u32)((P_TAG*)(p))->addr)

extern u32* g_world_active_otag_entries;

/* Link a GPU primitive into the secondary ordering table (libgpu addPrim). */
void world_append_gpu_primitive_to_secondary_otag(u32* prim) {
    u32* entries = g_world_active_otag_entries;

    setaddr(prim, getaddr(&entries[1]));
    setaddr(&entries[1], prim);
}
