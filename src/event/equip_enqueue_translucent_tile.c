#include "psx/gpu.h"
#include "psx/types.h"

typedef struct {
    u32 addr : 24;
    u32 len : 8;
} P_TAG;

#define setaddr(p, a) (((P_TAG*)(p))->addr = (u32)(a))
#define getaddr(p)    ((u32)((P_TAG*)(p))->addr)

typedef struct EquipTile {
    u32 tag;
    u8 r;
    u8 g;
    u8 b;
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} EquipTile;

typedef struct {
    u32* ot;          /* 0x00 */
    u8 pad[0x38];     /* 0x04 */
    EquipTile* tiles; /* 0x3c */
} EquipGfxCtx;

extern u16 g_equip_tile_count;
extern EquipGfxCtx* g_equip_graphics_context;

void equip_enqueue_translucent_tile(const RECT* rect, const u8* color,
    s32 semitrans, s32 otag_index) {
    EquipTile* tile;
    const RECT* tile_rect = rect;
    u16 index = g_equip_tile_count;

    g_equip_tile_count = index + 1;
    tile = &g_equip_graphics_context->tiles[index];
    tile->r = color[0];
    tile->g = color[1];
    tile->b = color[2];
    SetSemiTrans(tile, semitrans & 0xff);
    tile->x = tile_rect->x + 0x80;
    tile->y = tile_rect->y;
    tile->w = tile_rect->w;
    tile->h = tile_rect->h;
    {
        EquipGfxCtx* context = g_equip_graphics_context;
        setaddr(tile, getaddr(&context->ot[otag_index]));
        setaddr(&context->ot[otag_index], tile);
    }
}
