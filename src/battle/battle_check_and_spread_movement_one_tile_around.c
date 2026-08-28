#include "psx/types.h"

extern u8* g_battle_scratch_pad_ptr;
extern void (*g_spread_move_preset_table[])(void);
extern void battle_transfer_tiles_height_halves_and_slope_in_scratch_pad(void);
extern void battle_set_spreading_tile_x_and_y_coordinates(void);
extern s32 func_80175618(void);
extern s32 func_8017567C(s32 dir);
extern void func_80175958(s32 idx, s32 mode);

void battle_check_and_spread_movement_one_tile_around(void) {
    u8* ctx;
    s32 i;
    s32 j;

    ctx = g_battle_scratch_pad_ptr;
    battle_transfer_tiles_height_halves_and_slope_in_scratch_pad();
    for (i = 0; i < ctx[0x54]; i++) {
        ctx[0x40] = (i >= 4);
        g_spread_move_preset_table[i % 4]();
        battle_set_spreading_tile_x_and_y_coordinates();
        if ((func_80175618() == 0) && (func_8017567C(i) == 0)) {
            for (j = 0; j < ctx[0x55]; j++) {
                func_80175958(j, 0);
            }
        }
    }
}
