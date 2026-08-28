#include "psx/types.h"

extern void battle_store_selected_tile_coordinates(void* destination);
extern s32 func_8018401C(s32 mode, s32 x, s32 y, s32 z);
extern s16 g_battle_selected_tile_data;
extern s16 D_8014D02E;
extern s16 D_8014D030;
extern u16 g_battle_selected_tile_display_height;
extern s16 D_8014D034;
extern u8 D_8005E950[];

void battle_store_selected_tile_data(void) {
    s16 coords[3];
    s16* sel;
    s32 tmp;
    s32 idx;

    battle_store_selected_tile_coordinates(coords);
    sel = &g_battle_selected_tile_data;
    *sel = func_8018401C(0, coords[0], coords[2], coords[1]) & 0xFF;
    g_battle_selected_tile_display_height = func_8018401C(3, coords[0], coords[2], coords[1]) & 0xFF;
    g_battle_selected_tile_display_height += (func_8018401C(2, coords[0], coords[2], coords[1]) & 0xFF) * 2;
    tmp = func_8018401C(4, coords[0], coords[2], coords[1]) & 0xFF;
    D_8014D034 = tmp;
    g_battle_selected_tile_display_height += tmp * 2;
    idx = *sel * 2;
    D_8014D02E = D_8005E950[idx];
    D_8014D030 = D_8005E950[idx + 1];
}
