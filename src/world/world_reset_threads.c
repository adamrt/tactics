#include "fft/data.h"

void world_reset_threads(void) {
    s32* word;
    s32 i;

    /* Clear the whole 16 x 0x400 thread array, last word first. */
    word = (s32*)((u8*)g_world_threads + 0x3ffc);
    i = 0xfff;
    do {
        *word = 0;
        i--;
        word--;
    } while (i >= 0);
    g_world_current_thread_id = 0;
    g_world_threads->is_running = 1;
}
