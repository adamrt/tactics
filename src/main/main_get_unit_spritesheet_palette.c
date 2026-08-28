#include "fft/battle.h"

u8 main_get_unit_spritesheet_palette(battle_stats_t* unit, u8* palette) {
    u8 job_id;
    u8 sprite_set;

    *palette = 0;
    job_id = unit->job_id;
    sprite_set = unit->character_identity;
    if ((job_id == 0x5c) || (job_id == 0x5d)) {
        job_id--;
    }
    if (sprite_set < 0x80) {
        return sprite_set;
    }
    if (sprite_set == 0x80) {
        sprite_set = job_id * 2 - 0x34;
        return sprite_set;
    }
    if (sprite_set == 0x81) {
        sprite_set = job_id * 2 - 0x33;
        return sprite_set;
    }
    if (sprite_set == 0x82) {
        *palette = unit->job_portrait_palette;
        return unit->spritesheet_id;
    }
    sprite_set = job_id + 0x28;
    return sprite_set;
}
