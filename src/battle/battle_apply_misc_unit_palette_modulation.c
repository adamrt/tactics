#include "fft/battle.h"

extern battle_misc_data_t* battle_get_unit_misc_data_by_misc_id(u32 misc_id);
extern void battle_copy_misc_data_xyz_values(s16* destination,
    const u8* misc_data);
extern u8* battle_get_tile_data_pointer(s32 x, s32 y, s32 elevation);
extern void battle_palette_modification(
    s32 preset_color, s32 time, s32 palette_group, s32 palette_index,
    s32 unused, s32 red, s32 green, s32 blue);

void battle_apply_misc_unit_palette_modulation(
    s32 preset_color, s32 time, s32 misc_id,
    s32 red, s32 green, s32 blue) {
    battle_svector_t screen_coordinates;
    battle_misc_data_t* unit;
    u8* tile;
    u16 red_copy;
    u16 green_copy;
    u16 blue_copy;

    unit = battle_get_unit_misc_data_by_misc_id(misc_id & 0xffff);
    red_copy = red;
    green_copy = green;
    blue_copy = blue;
    if (unit == 0) {
        return;
    }

    battle_copy_misc_data_xyz_values((s16*)&screen_coordinates,
        (const u8*)unit);
    tile = battle_get_tile_data_pointer(
        screen_coordinates.vx / 28,
        screen_coordinates.vz / 28,
        unit->map_z);

    battle_palette_modification(
        preset_color, time, 3, misc_id, 0,
        (s16)red_copy, (s16)green_copy, (s16)blue_copy);

    if ((tile[3] & 0xe0) != 0
        && unit->screen_z >= -(tile[2] + (tile[3] >> 5)) * 12) {
        battle_palette_modification(
            preset_color, time, 4, misc_id, 0,
            (s16)red_copy, (s16)green_copy, (s16)blue_copy);
    } else {
        battle_palette_modification(
            preset_color, time, 4, misc_id, 0,
            (s16)-red_copy, (s16)-green_copy, (s16)-blue_copy);
    }
}
