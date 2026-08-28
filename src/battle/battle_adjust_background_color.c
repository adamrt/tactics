#include "psx/types.h"

extern u8 g_battle_background_color[];
extern void func_800e77b8(s32 mode, s32 red, s32 green, s32 blue);

void battle_adjust_background_color(s32 red_delta, s32 green_delta,
    s32 blue_delta) {
    {
        u8* red = &g_battle_background_color[0];
        /* Pin: the target sign-extends red_delta in place in $a0 after
         * copying the parameter to $a3 (`move a3,a0`). An s16 local or a
         * cast both compute the extension in $v0 instead. */
        register s32 red_for_compare __asm__("$4") = red_delta;
        s32 current = red[0];

        __asm__("" : "=r"(red_for_compare) : "0"(red_for_compare));
        if (current + (s16)red_for_compare < current) {
            red[0] = 0xff;
        } else {
            red[0] = red_delta + red[0];
        }
    }

    /* The retail routine reuses red_delta for the green underflow test. */
    {
        u8* green = &g_battle_background_color[1];
        s32 current = green[0];

        if (current + (s16)red_delta < current) {
            green[0] = 0xff;
        } else {
            green[0] = green_delta + green[0];
        }
    }

    {
        u8* blue = &g_battle_background_color[2];
        s32 current = blue[0];

        if (current + (s16)blue_delta < current) {
            blue[0] = 0xff;
        } else {
            blue[0] = blue_delta + blue[0];
        }
    }

    func_800e77b8(9, g_battle_background_color[0], g_battle_background_color[1],
        g_battle_background_color[2]);
}
