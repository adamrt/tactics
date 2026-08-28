#include "psx/types.h"

extern u8 g_game_allocator_table[];

void main_clear_game_allocator_table(void) {
    int index = 63;
    u8* entry = &g_game_allocator_table[63];

    for (; index >= 0; index--, entry--) {
        *entry = 0;
    }
}
