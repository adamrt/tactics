#include "psx/gpu.h"
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

extern u8 g_battle_numeric_display_frame_offsets[12][8];
extern RECT g_battle_numeric_display_texture_window;
extern RECT g_battle_disabled_texture_window;

extern void battle_initialize_menu_primitive_colors_palette_bank_0(void* menu);
extern void battle_initialize_semitransparent_menu_sprt(void* sprite);

void battle_initialize_numeric_display_frame_primitives(const u16* bounds, u8* menu) {
    s32 table_offset;
    s32 index;
    u8* packet;
    MenuLineF2* line;

    packet = menu + 0x18;
    index = 0;
    do {
        SetLineF2(packet);
        index++;
        packet += 0x10;
    } while (index < 12);

    battle_initialize_menu_primitive_colors_palette_bank_0(menu);
    table_offset = 0;
    index = 0;
    line = (MenuLineF2*)(menu + 0x18);
    do {
        line->x0 = (s8)g_battle_numeric_display_frame_offsets[0][table_offset] + bounds[0];
        line->y0 = (s8)g_battle_numeric_display_frame_offsets[0][table_offset + 1] + bounds[1];
        line->x1 = (s8)g_battle_numeric_display_frame_offsets[0][table_offset + 2] + bounds[0];
        line->y1 = (s8)g_battle_numeric_display_frame_offsets[0][table_offset + 3] + bounds[1];
        if (*(s8*)&g_battle_numeric_display_frame_offsets[0][table_offset + 4] != 0) {
            line->x0 += bounds[2];
        }
        if (*(s8*)&g_battle_numeric_display_frame_offsets[0][table_offset + 5] != 0) {
            line->y0 += bounds[3];
        }
        if (*(s8*)&g_battle_numeric_display_frame_offsets[0][table_offset + 6] != 0) {
            line->x1 += bounds[2];
        }
        if (*(s8*)&g_battle_numeric_display_frame_offsets[0][table_offset + 7] != 0) {
            line->y1 += bounds[3];
        }
        table_offset += 8;
        index++;
        line++;
    } while (index < 12);

    SetDrawMode((DR_MODE*)(menu + 0x0c), 1, 0,
        (u16)GetTPage(0, 0, 0x3c0, 0x100),
        &g_battle_numeric_display_texture_window);
    SetDrawMode((DR_MODE*)menu, 0, 0,
        (u16)GetTPage(0, 2, 0x3c0, 0x100),
        &g_battle_disabled_texture_window);
    battle_initialize_semitransparent_menu_sprt(menu + 0xd8);
    *(u16*)(menu + 0xe0) = bounds[0];
    *(u16*)(menu + 0xe2) = bounds[1];
    *(u16*)(menu + 0xe8) = bounds[2];
    *(u16*)(menu + 0xea) = bounds[3];
}
