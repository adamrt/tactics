#include "psx/types.h"

extern void func_8014CA80(void);
extern s32 g_screen_fade;

void battle_tutorial_thread_switching_for_eventend(void) {
    g_screen_fade = 0;
    do {
        func_8014CA80();
        g_screen_fade += 4;
    } while (g_screen_fade < 0x100);
    g_screen_fade = 0xff;
}
