#include "psx/types.h"

extern u8 g_battle_tpage7_vram_allocation_grid[15][16];

/* Clear the 15-by-16 allocation grid consumed by the tpage-7 VRAM allocator. */
void battle_clear_tpage7_vram_allocation_grid(void) {
    s32 row;
    s32 column;

    row = 0;
    do {
        column = 15;
        do {
            g_battle_tpage7_vram_allocation_grid[row][column] = 0;
            column--;
        } while (column >= 0);
        row++;
    } while (row < 15);
}
