#include "psx/types.h"

extern u8* battle_get_tile_data_pointer(s32 x, s32 z, s32 y);

void battle_tile_coords_to_world_coords(s16* in, s32* out) {
    u8* tile;

    tile = battle_get_tile_data_pointer(in[0], in[2], in[1]);
    out[0] = in[0] * 28 + 14;
    out[2] = in[2] * 28 + 14;
    out[1] = -(tile[2] * 12);
}
