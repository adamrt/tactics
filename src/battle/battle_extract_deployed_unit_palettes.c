#include "psx/types.h"

extern u16 D_80094AE4[2][16];
extern u16 D_80094B44[16];
extern u16 D_80094B64[16];
extern u16 D_80094BC4[16];
extern u16 D_80094BE4[16];

extern void battle_load_map_palette_data(u16*, s32, s32, s32);

void battle_extract_deployed_unit_palettes(void) {
    s32 unused[2];

    battle_load_map_palette_data(D_80094AE4[0], 2, 1, 0);
    battle_load_map_palette_data(D_80094AE4[1], 2, 2, 0);
    battle_load_map_palette_data(D_80094B44, 2, 3, 0);
    battle_load_map_palette_data(D_80094B64, 2, 4, 0);
    battle_load_map_palette_data(D_80094BC4, 2, 5, 0);
    battle_load_map_palette_data(D_80094BE4, 2, 7, 0);
    (void)&unused;
}
