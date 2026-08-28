#include "psx/gpu.h"

extern void world_initialize_menu_sprite(SPRT* sprite);

/* Initialize an array of WORLD menu sprites with a shared CLUT. */
void world_initialize_menu_sprite_array(SPRT* sprites, s32 count, s32 clut) {
    SPRT* sprite = sprites;
    s32 saved_count = count;
    s32 saved_clut = clut;
    s32 index;
    volatile u8 unused_stack[8];

    /* Emits nothing; it makes the count/clut copies into $s2/$s3 precede the
     * `move s1,zero` of index, as in the target. */
    __asm__("" : : "r"(saved_count), "r"(saved_clut));
    index = 0;
    if (saved_count > 0) {
        do {
            world_initialize_menu_sprite(sprite);
            sprite->clut = saved_clut;
            index += 1;
            sprite++;
        } while (index < saved_count);
    }
}
