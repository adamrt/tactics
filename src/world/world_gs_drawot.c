#include "psx/gpu.h"
#include "psx/types.h"

typedef struct {
    u8 pad[0x10];
    u32 ot;
} WorldGsDrawOtArg;

void world_gs_drawot(WorldGsDrawOtArg* arg) {
    DrawOTag(arg->ot);
}
