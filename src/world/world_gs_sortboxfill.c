#include "psx/types.h"

typedef struct {
    s32 attribute; /* 0x00 */
    s16 x;         /* 0x04 */
    s16 y;         /* 0x06 */
    u16 w;         /* 0x08 */
    u16 h;         /* 0x0A */
    u8 r;          /* 0x0C */
    u8 g;          /* 0x0D */
    u8 b;          /* 0x0E */
    u8 pad;        /* 0x0F */
} WorldBoxF;

typedef struct {
    u32 tag;  /* 0x00 */
    u32 mode; /* 0x04 */
    u8 r0;    /* 0x08 */
    u8 g0;    /* 0x09 */
    u8 b0;    /* 0x0A */
    u8 code;  /* 0x0B */
    s16 x0;   /* 0x0C */
    s16 y0;   /* 0x0E */
    u16 w;    /* 0x10 */
    u16 h;    /* 0x12 */
} WorldTile;

extern WorldTile* g_world_gs_out_packet_p;
extern u16 g_world_gs_offset_x;
extern u16 g_world_gs_offset_y;

extern WorldTile* func_800E03EC(WorldTile*, void*, u16, s32);

void world_gs_sortboxfill(WorldBoxF* bp, void* otp, s32 pri) {
    WorldTile* p;
    s32 attr;
    u32 hi;
    u32 lo;

    attr = bp->attribute;
    if (attr >= 0) {
        p = g_world_gs_out_packet_p;
        hi = (attr >> 17) & 0x180;
        lo = ((attr >> 23) & 0x60) | 0xE1000200;
        p->mode = hi | lo;
        p->r0 = bp->r;
        p->g0 = bp->g;
        p->b0 = bp->b;
        p->code = ((attr >> 29) & 2) | 0x60;
        p->x0 = bp->x + g_world_gs_offset_x;
        p->y0 = bp->y + g_world_gs_offset_y;
        p->w = bp->w;
        p->h = bp->h;
        g_world_gs_out_packet_p = func_800E03EC(p, otp, pri, 4);
    }
}
