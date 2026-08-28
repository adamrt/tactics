#include "fft/battle.h"
#include "psx/types.h"

extern battle_ai_data_t g_ai_data_base;

/* Count the set bits of two 18-row tile bitmaps (rows of 16 tiles, the second
 * bitmap following the first) that fall inside the map's X/Y extent. */
s32 battle_count_flagged_tiles_within_map_bounds(u16* rows) {
    battle_ai_data_t* ai;
    register s32 count __asm__("$9");
    register s32 bitmap __asm__("$11");
    s32 y;
    s32 x;
    u16 row;

    count = 0;
    ai = &g_ai_data_base;
    bitmap = 0;
    do {
        __asm__("" : "=r"(bitmap) : "0"(bitmap));
        for (y = 0; y < ai->map_max_y; y++) {
            row = rows[y];
            if (row != 0) {
                for (x = 0; x < ai->map_max_x; x++) {
                    if (((row << x) & 0x8000) != 0) {
                        count++;
                    }
                }
            }
        }
        rows += 0x12;
        bitmap++;
    } while (bitmap < 2);
    return count;
}
