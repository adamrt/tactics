#include "fft/battle.h"

extern u8 main_get_unit_spritesheet_palette(battle_stats_t* unit, u8* palette);

u8 main_calculate_unit_palette_spritesheet(battle_stats_t* unit, u8* palette) {
    u8 spritesheet = main_get_unit_spritesheet_palette(unit, palette);

    unit->spritesheet_id = spritesheet;
    unit->job_portrait_palette = *palette;
    return spritesheet;
}
