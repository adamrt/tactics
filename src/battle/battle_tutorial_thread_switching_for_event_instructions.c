#include "psx/types.h"

extern void func_8014CA80(void);
extern s32 g_screen_fade;

void battle_tutorial_thread_switching_for_event_instructions(void) {
    g_screen_fade = 0xFF;
    do {
        func_8014CA80();
        g_screen_fade -= 4;
    } while ((s32)g_screen_fade > 0);
    g_screen_fade = 0;
}
