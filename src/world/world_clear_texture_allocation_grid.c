#include "psx/types.h"

extern u8 g_world_texture_allocation_grid[15][16];

void world_clear_texture_allocation_grid(void) {
    s32 row;
    s32 column;

    for (row = 0; row < 15; row++) {
        for (column = 15; column >= 0; column--) {
            g_world_texture_allocation_grid[row][column] = 0;
        }
    }
}
