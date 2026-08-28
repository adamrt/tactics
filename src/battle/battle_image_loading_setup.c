#include "psx/types.h"

extern void DrawPrim(void* prim);
extern u16 g_etc_graphics_enabled;
extern s32* g_current_otag_entry;

void battle_image_loading_setup(s32* prim) {
    s32* otag;

    if (g_etc_graphics_enabled != 0) {
        DrawPrim(prim);
        return;
    }
    otag = g_current_otag_entry;
    *prim = (*prim & 0xFF000000) | (*otag & 0xFFFFFF);
    *otag = (*otag & 0xFF000000) | ((s32)prim & 0xFFFFFF);
}
