#include "psx/types.h"

/* Psy-Q LINE_F2 layout; psx/gpu.h only declares SetLineF2(void *). */
typedef struct MenuLineF2 {
    u32 tag;
    u8 r0;
    u8 g0;
    u8 b0;
    u8 code;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;
} MenuLineF2;

extern u8 g_battle_numeric_display_palette_indices[12];
extern u8 g_battle_menu_palette_colors[];

void battle_initialize_menu_primitive_colors_palette_bank_0(u8* menu) {
    s32 index;
    s32 palette_offset;
    MenuLineF2* line;

    index = 0;
    line = (MenuLineF2*)(menu + 0x18);
    do {
        palette_offset = g_battle_numeric_display_palette_indices[index] * 2;
        line->r0 = (*(volatile u8*)(g_battle_menu_palette_colors + palette_offset) & 0x1f) << 3;
        line->g0 = (*(volatile u16*)(g_battle_menu_palette_colors + palette_offset) >> 2) & 0xf8;
        index++;
        line->b0 = (*(volatile u16*)(g_battle_menu_palette_colors + palette_offset) >> 7) & 0xf8;
        line++;
    } while (index < 12);
    *(u16*)(menu + 0xe6) = 0x7c3c;
}
