#include "psx/gpu.h"

extern void battle_initialize_semitransparent_menu_sprt(SPRT* sprite);

/* Initialize an array of BATTLE menu sprites with a shared CLUT. */
void battle_initialize_battle_menu_sprite_array(SPRT* sprites, s32 count, s32 clut) {
    SPRT* sprite = sprites;
    s32 saved_count = count;
    s32 saved_clut = clut;
    s32 index;
    volatile u8 unused_stack[8];

    /* Emits nothing; without it GCC saves count/clut in $s1/$s2 one slot
     * lower and drops the $s2 spill (frame layout changes, same size). */
    __asm__("" : : "r"(saved_count), "r"(saved_clut));
    index = 0;
    if (saved_count > 0) {
        do {
            battle_initialize_semitransparent_menu_sprt(sprite);
            sprite->clut = saved_clut;
            index += 1;
            sprite++;
        } while (index < saved_count);
    }
}
