#include "fft/battle.h"
#include "psx/types.h"

/* The target handles 0x12..0x13 as one halfword; the header has a byte. */
#define SPRITE_FLAGS_HALF(unit) (*(u16*)&(unit)->sprite_display_flags)

void battle_update_sprite_transparency_flag(battle_misc_data_t* unit) {
    u16 sprite_flags;

    if ((unit->status_flags_5_6 & 0x10) != 0) {
        sprite_flags = (SPRITE_FLAGS_HALF(unit) & 0xff9f) | 1;
    } else {
        sprite_flags = SPRITE_FLAGS_HALF(unit) & 0xfffe;
    }
    SPRITE_FLAGS_HALF(unit) = sprite_flags;
}
