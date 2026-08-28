#include "fft/battle.h"

void battle_store_sprite_display_data(u8* base, s32 index, u8 x_shift, u8 y_shift,
    u16 u, u16 v, u16 width, u16 height,
    u16 flags) {
    s32 offset;
    battle_sprite_part_display_data_t* part;

    offset = index * sizeof(battle_sprite_part_display_data_t) + 14;
    part = (battle_sprite_part_display_data_t*)(base + offset);
    part->x_shift = x_shift;
    part->y_shift = y_shift;
    part->u = u;
    part->v = v;
    part->width = width;
    part->height = height;
    part->flags = flags;
}
