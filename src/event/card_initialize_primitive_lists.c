#include "psx/gpu.h"
#include "psx/types.h"

typedef struct CardPrimitiveLists {
    u8 unknown_00[0x10];
    POLY_FT4* polygons;
    u8 unknown_14[0x28];
    u8* tiles;
} CardPrimitiveLists;

extern u16 g_card_poly_ft4_capacity;
extern u16 g_card_tile_capacity;

void card_initialize_primitive_lists(CardPrimitiveLists* lists) {
    s32 i;

    for (i = 0; i < g_card_poly_ft4_capacity; i++) {
        SetPolyFT4(&lists->polygons[i]);
        SetShadeTex(&lists->polygons[i], 0);
    }
    for (i = 0; i < g_card_tile_capacity; i++) {
        SetTile(lists->tiles + i * 0x10);
    }
}
