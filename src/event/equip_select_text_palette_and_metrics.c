#include "psx/types.h"

extern u8 g_equip_compact_layout;
extern u8 g_equip_sprite_color;
extern u8 g_equip_sprite_color_g;
extern u8 g_equip_sprite_color_b;

extern u16 D_801D86BC;
extern u16 D_801D86BE;
extern u16 D_801D86C0;
extern u16 D_801D86C2;
extern u16 D_801D86C4;
extern u16 D_801D86C6;
extern u16 D_801D86CA;
extern u16 D_801D86CC;
extern u16 D_801D86CE;
extern u16 D_801D86D0;
extern u16 D_801D86E0;
extern u16 D_801D86E2;

extern u16 D_801E9088;
extern u16 D_801E90D0;
extern u16 D_801E90F4;
extern u16 D_801E92D0;
extern u16 D_801E92DC;
extern u16 D_801E92FC;

/* Select the compact or full equip window layout. */
void equip_select_text_palette_and_metrics(s32 compact) {
    g_equip_compact_layout = compact;
    if (compact != 0) {
        g_equip_sprite_color = 0x60;
        g_equip_sprite_color_g = 0x60;
        g_equip_sprite_color_b = 0x80;
        D_801E92D0 = D_801D86E2;
        D_801E90F4 = D_801D86C0;
        D_801E90D0 = D_801D86BE;
        D_801E9088 = D_801D86C6;
        D_801E92DC = D_801D86CE;
        D_801E92FC = D_801D86D0;
    } else {
        g_equip_sprite_color = 0x80;
        g_equip_sprite_color_g = 0x80;
        g_equip_sprite_color_b = 0x80;
        D_801E92D0 = D_801D86E0;
        D_801E90F4 = D_801D86C2;
        D_801E90D0 = D_801D86BC;
        D_801E9088 = D_801D86C4;
        D_801E92DC = D_801D86CA;
        D_801E92FC = D_801D86CC;
    }
}
