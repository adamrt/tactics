#include "psx/types.h"

extern void* g_world_menu_window_buffer_pointers[3][2];

void world_clear_menu_window_buffer_pointers(void) {
    void* empty = (void*)-1;
    s32 index;

    index = 5;
    do {
        ((void**)g_world_menu_window_buffer_pointers)[index] = empty;
        index--;
    } while (index >= 0);
}
