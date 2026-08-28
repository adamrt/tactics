#include "psx/gte.h"
#include "psx/types.h"

extern void func_8001D188(s32, s32, s32);

extern s16 g_world_gs_offset_y;
extern s16 g_world_gs_offset_x;

void world_gs_gte_init(void) {
    InitGeom();
    func_8001D188(0, 0, 0);
    SetGeomOffset(0, 0);
    g_world_gs_offset_y = 0;
    g_world_gs_offset_x = 0;
}
