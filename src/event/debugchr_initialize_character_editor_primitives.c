#include "psx/gpu.h"
#include "psx/types.h"

extern void SetLineF2(void* primitive);
extern void initialize_menu_draw_mode_packet(void* state, s32 first, s32 second);

/* libgpu TILE / LINE_F2 packets (same layout as EquipTile / EquipLineF2 in
 * equip_enqueue_translucent_tile.c / equip_enqueue_line_f2.c, with the code
 * byte spelled out). */
typedef struct DebugChrMenuTile {
    u32 tag;
    u8 r, g, b, code;
    s16 x, y, w, h;
} DebugChrMenuTile;

typedef struct DebugChrMenuLineF2 {
    u32 tag;
    u8 r, g, b, code;
    s16 x0, y0, x1, y1;
} DebugChrMenuLineF2;

/* Menu primitive block: three DR_MODE packets (initialize_menu_draw_mode_packet
 * fills them), two translucent backdrop tiles and eight frame lines.  The
 * region between is not touched here. */
typedef struct DebugChrMenuPrimitives {
    DR_MODE draw_modes[3]; /* 0x000 */
    u8 _pad024[0x1e0];
    DebugChrMenuTile tiles[2];   /* 0x204 */
    DebugChrMenuLineF2 lines[8]; /* 0x224 */
} DebugChrMenuPrimitives;

/* The halfword stores go through volatile so they stay in source order. */
#define LINE(n) (((volatile DebugChrMenuLineF2*)menu->lines)[n])

void debugchr_initialize_character_editor_primitives(DebugChrMenuPrimitives* menu) {
    s32 i;
    s32 shared_value;
    s32 ten;
    /* Pins + the `ten` fence: the two byte-store groups (0x20 then 0x10)
     * must stay in source order and the call arguments are materialised
     * early; without them GCC swaps the groups (volatile stores do not
     * hold the order either). */
    register s32 one asm("$6");
    register DebugChrMenuPrimitives* call_menu asm("$4");
    register s32 first asm("$5");

    SetTile(&menu->tiles[0]);
    SetTile(&menu->tiles[1]);
    SetSemiTrans(&menu->tiles[0], 1);
    SetSemiTrans(&menu->tiles[1], 1);
    menu->tiles[0].r = 0x30;
    menu->tiles[0].g = 0x30;
    menu->tiles[0].b = 0x30;
    menu->tiles[1].r = 0x30;
    menu->tiles[1].g = 0x30;
    menu->tiles[1].b = 0x30;
    menu->tiles[0].x = 0x12;
    menu->tiles[0].y = 1;
    menu->tiles[0].w = 0x10;
    menu->tiles[0].h = 0x5a;
    menu->tiles[1].x = 0x7c;
    menu->tiles[1].y = 1;
    menu->tiles[1].w = 0x10;
    menu->tiles[1].h = 0x5a;
    for (i = 0; i < 8; i++) {
        SetLineF2(&menu->lines[i]);
        SetSemiTrans(&menu->lines[i], 1);
    }
    call_menu = menu;
    first = 0;
    shared_value = 0x10;
    ten = 0x20;
    menu->lines[1].r = 0x20;
    menu->lines[1].g = 0x20;
    menu->lines[1].b = 0x20;
    menu->lines[2].r = 0x20;
    menu->lines[2].g = 0x20;
    menu->lines[2].b = 0x20;
    menu->lines[5].r = 0x20;
    menu->lines[5].g = 0x20;
    menu->lines[5].b = 0x20;
    menu->lines[6].r = 0x20;
    menu->lines[6].g = 0x20;
    menu->lines[6].b = 0x20;
    ten = 0x10;
    __asm__ volatile("" : : "r"(ten));
    one = 1;
    menu->lines[0].r = shared_value;
    menu->lines[0].g = shared_value;
    menu->lines[0].b = shared_value;
    menu->lines[3].r = shared_value;
    menu->lines[3].g = shared_value;
    menu->lines[3].b = shared_value;
    menu->lines[4].r = shared_value;
    menu->lines[4].g = shared_value;
    menu->lines[4].b = shared_value;
    menu->lines[7].r = shared_value;
    menu->lines[7].g = shared_value;
    menu->lines[7].b = shared_value;
    shared_value = 0x5a;
    LINE(0).x0 = ten;
    LINE(0).x1 = ten;
    LINE(1).x0 = 0x11;
    LINE(1).x1 = 0x11;
    LINE(0).y0 = one;
    LINE(0).y1 = shared_value;
    LINE(1).y0 = one;
    LINE(1).y1 = shared_value;
    LINE(2).x0 = 0x22;
    LINE(2).y0 = one;
    LINE(2).x1 = 0x22;
    LINE(3).x0 = 0x23;
    LINE(3).x1 = 0x23;
    LINE(4).x0 = 0x7a;
    LINE(4).x1 = 0x7a;
    LINE(5).x0 = 0x7b;
    LINE(5).x1 = 0x7b;
    LINE(6).x0 = 0x8c;
    LINE(6).x1 = 0x8c;
    LINE(2).y1 = shared_value;
    LINE(3).y0 = one;
    LINE(3).y1 = shared_value;
    LINE(4).y0 = one;
    LINE(4).y1 = shared_value;
    LINE(5).y0 = one;
    LINE(5).y1 = shared_value;
    LINE(6).y0 = one;
    LINE(6).y1 = shared_value;
    LINE(7).x0 = 0x8d;
    LINE(7).y0 = one;
    LINE(7).x1 = 0x8d;
    menu->lines[7].y1 = shared_value;
    initialize_menu_draw_mode_packet(call_menu, first, one);
    initialize_menu_draw_mode_packet(&menu->draw_modes[1], 2, one);
    initialize_menu_draw_mode_packet(&menu->draw_modes[2], 4, one);
}
