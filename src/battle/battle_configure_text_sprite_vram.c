#include "psx/gpu.h"
#include "psx/types.h"

extern void battle_allocate_tpage7_vram(RECT* rect, SPRT* sprite,
    const void* image_data);

void battle_configure_text_sprite_vram(RECT* rect, s16 width, s16 height,
    SPRT* sprite, s32 palette_row) {
    rect->w = width;
    rect->h = height;
    battle_allocate_tpage7_vram(rect, sprite, (const void*)-1);
    sprite->clut = (palette_row << 4) + 0x7c3c;
}
